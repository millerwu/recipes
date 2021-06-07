
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "ion_4.19.h"

#define ION_SYSTEM_HEAP_ID 25        // Get from kernel header ion.h, different platform may have different valye, related to platform.
#define ION_HEAP_TYPE_SYSTEM_MASK (0x1 << ION_SYSTEM_HEAP_ID)

typedef int ion_user_handle_t;
size_t len = 1024 * 1024, align = 0;
int prot = PROT_READ | PROT_WRITE;
int map_flags = MAP_SHARED;
u_int32_t alloc_flags = ION_FLAG_CACHED;
u_int32_t heap_mask = ION_HEAP_TYPE_SYSTEM_MASK;
int test = -1;
size_t stride;

int ion_open()
{
    int fd = open("/dev/ion", O_RDONLY);
    if (fd < 0) printf("open /dev/ion failed: %s", strerror(errno));

    return fd;
}

int ion_close(int fd)
{
    int ret = close(fd);
    if (ret < 0) return -errno;
    return ret;
}

int _ion_alloc_test(int *fd, ion_user_handle_t *handle)
{
    int ret = 0;

    printf("ion_allocation_data size = %d\n",
           (int)sizeof(struct ion_allocation_data));

    printf("ION_IOC_ALLOC = 0x%x \n",
           (unsigned)ION_IOC_ALLOC);

    *fd = ion_open();
    if (*fd < 0)
        return *fd;

    printf("ion_alloc debug\n");
    int a = align;

    if (handle == NULL) return -EINVAL;

    struct ion_allocation_data data = {
        .len = len,
        .heap_id_mask = heap_mask,
        .flags = alloc_flags,
    };

    ret = ioctl(*fd, ION_IOC_ALLOC, &data);
    printf("ION_IOC_NEW_ALLOC ret = %d \n", ret);
    if (ret < 0) return ret;

    *handle = data.fd;

    printf("ion_alloc debug \n");

    if (ret)
        printf("%s failed: %s\n", __func__, strerror(ret));
    return ret;
}

void ion_alloc_test()
{
    int fd, ret;
    ion_user_handle_t handle;

    printf("ion_allocation_data size = %d\n",
           (int)sizeof(struct ion_allocation_data));

    if (_ion_alloc_test(&fd, &handle))
        return;

    ion_close(fd);
    printf("ion alloc test: passed\n");
}

void ion_share_test()
{
    ion_user_handle_t handle;
    int sd[2];
    int num_fd = 1;
    struct iovec count_vec = {
        .iov_base = &num_fd,
        .iov_len = sizeof num_fd,
    };
    char buf[CMSG_SPACE(sizeof(int))];
    // Use Socket to implement IPC.
    socketpair(AF_UNIX, SOCK_STREAM, 0, sd);
    if (fork())
    {
        struct msghdr msg = {
            .msg_control = buf,
            .msg_controllen = sizeof buf,
            .msg_iov = &count_vec,
            .msg_iovlen = 1,
        };

        struct cmsghdr *cmsg;
        int fd;
        char *ptr;
        /* parent */
        if (_ion_alloc_test(&fd, &handle))
            return;
        ptr = (char *)mmap(NULL, len, prot, map_flags, handle, 0);
        if (ptr == MAP_FAILED)
        {
            return;
        }
        strcpy(ptr, "master");
        cmsg = CMSG_FIRSTHDR(&msg);
        cmsg->cmsg_level = SOL_SOCKET;
        cmsg->cmsg_type = SCM_RIGHTS;
        cmsg->cmsg_len = CMSG_LEN(sizeof(int));
        *(int *)CMSG_DATA(cmsg) = handle;
        /* send the fd */
        printf("master? [%10s] should be [master]\n", ptr);
        printf("master sending msg 1\n");
        sendmsg(sd[0], &msg, 0);
        if (recvmsg(sd[0], &msg, 0) < 0)
            perror("master recv msg 2");
        printf("master? [%10s] should be [child]\n", ptr);

        /* send ping */
        sendmsg(sd[0], &msg, 0);
        printf("master->master? [%10s]\n", ptr);
        if (recvmsg(sd[0], &msg, 0) < 0)
            perror("master recv 1");
        close(fd);
        _exit(0);
    }
    else
    {
        struct cmsghdr *cmsg;
        char *ptr;
        int fd, recv_fd;
        char *child_buf[100];
        /* child */
        struct iovec count_vec = {
            .iov_base = child_buf,
            .iov_len = sizeof child_buf,
        };

        struct msghdr child_msg = {
            .msg_control = buf,
            .msg_controllen = sizeof buf,
            .msg_iov = &count_vec,
            .msg_iovlen = 1,
        };

        if (recvmsg(sd[1], &child_msg, 0) < 0)
            perror("child recv msg 1");
        cmsg = CMSG_FIRSTHDR(&child_msg);
        if (cmsg == NULL)
        {
            printf("no cmsg rcvd in child");
            return;
        }
        recv_fd = *(int *)CMSG_DATA(cmsg);
        if (recv_fd < 0)
        {
            printf("could not get recv_fd from socket");
            return;
        }
        printf("child %d\n", recv_fd);
        fd = ion_open();
        ptr = (char *)mmap(NULL, len, prot, map_flags, recv_fd, 0);
        if (ptr == MAP_FAILED)
        {
            return;
        }
        printf("child? [%10s] should be [master]\n", ptr);
        strcpy(ptr, "child");
        printf("child sending msg 2\n");
        sendmsg(sd[1], &child_msg, 0);
        close(fd);
    }
}

int main(int argc, char *argv[])
{
    int c;
    enum tests
    {
        ALLOC_TEST = 0,
        SHARE_TEST,
    };

    while (1)
    {
        static struct option opts[] = {
            {"alloc", no_argument, 0, 'a'},
            {"alloc_flags", required_argument, 0, 'f'},
            {"heap_mask", required_argument, 0, 'h'},
            {"share", no_argument, 0, 's'},
            {"len", required_argument, 0, 'l'},
            {"align", required_argument, 0, 'g'},
            {"map_flags", required_argument, 0, 'z'},
            {"prot", required_argument, 0, 'p'},
        };
        int i = 0;
        c = getopt_long(argc, argv, "af:h:l:r:st", opts, &i);
        if (c == -1)
            break;

        switch (c)
        {
            case 'l':
                len = atol(optarg);
                break;
            case 'g':
                align = atol(optarg);
                break;
            case 'z':
                map_flags = 0;
                map_flags |= strstr(optarg, "PROT_EXEC") ? PROT_EXEC : 0;
                map_flags |= strstr(optarg, "PROT_READ") ? PROT_READ : 0;
                map_flags |= strstr(optarg, "PROT_WRITE") ? PROT_WRITE : 0;
                map_flags |= strstr(optarg, "PROT_NONE") ? PROT_NONE : 0;
                break;
            case 'p':
                prot = 0;
                prot |= strstr(optarg, "MAP_PRIVATE") ? MAP_PRIVATE : 0;
                prot |= strstr(optarg, "MAP_SHARED") ? MAP_SHARED : 0;
                break;
            case 'f':
                alloc_flags = atol(optarg);
                break;
            case 'h':
                heap_mask = atol(optarg);
                break;
            case 'a':
                test = ALLOC_TEST;
                break;
            case 's':
                test = SHARE_TEST;
                break;
        }
    }
    printf(
        "test %d, len %zu, align %zu, map_flags %d, prot %d, heap_mask %d,"
        " alloc_flags %d\n",
        test, len, align, map_flags, prot,
        heap_mask, alloc_flags);
    switch (test)
    {
        case ALLOC_TEST:
            ion_alloc_test();
            break;
        case SHARE_TEST:
            ion_share_test();
            break;
        default:
            printf("must specify a test (alloc, map, share)\n");
    }
    return 0;
}

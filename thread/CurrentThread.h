//
// Created by wu on 17-8-14.
//

#ifndef FAKE_THREAD_CURRENTTHREAD_H
#define FAKE_THREAD_CURRENTTHREAD_H

#include <string>
#include <unistd.h>
#include <sys/syscall.h>

namespace fake {

  pid_t GetTid() {
    return static_cast<pid_t >(::syscall(SYS_gettid));
  }

  namespace CurrentThread {
    __thread pid_t t_cached_Tid;
    __thread const char* t_threadName = "unknown";

    pid_t tid() {
      if (t_cached_Tid == 0) {
        t_cached_Tid = GetTid();
      }
      return t_cached_Tid;
    }

    bool isMainThread() {
      return tid() == getpid();
    }
  }


}

#endif //FAKE_THREAD_CURRENTTHREAD_H

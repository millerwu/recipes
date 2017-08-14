//
// Created by wu on 17-8-14.
//

#ifndef FAKE_THREAD_CURRENTTHREAD_H
#define FAKE_THREAD_CURRENTTHREAD_H

namespace fake {
  namespace CurrentThread {
    __thread pid_t t_cached_Tid;

    pid_t tid() {
      if (t_cached_Tid == 0) {
        t_cached_Tid = GetTid();
      }
      return t_cached_Tid;
    }
  }

  pid_t GetTid() {
    return static_cast<pid_t >(::syscall(SYS_gettid));
  }
}

#endif //FAKE_THREAD_CURRENTTHREAD_H

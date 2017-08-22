//
// Created by wu on 17-8-14.
//

#ifndef FAKE_THREAD_MUTEX_H
#define FAKE_THREAD_MUTEX_H

#include "NonCopyable.h"
#include "CurrentThread.h"
#include <pthread.h>
#include <assert.h>


namespace fake {
  class MutexLock : NonCopyable {
  public:
    MutexLock()
      : holder_(0)
    {
      pthread_mutex_init(&mutex_, NULL);
    }

    ~MutexLock() {
      assert(holder_==0);
      pthread_mutex_destroy(&mutex_);
    }

    void Lock() {
      pthread_mutex_lock(&mutex_);
      holder_ = CurrentThread::tid();
    }

    void Unlock() {
      holder_ = 0;
      pthread_mutex_unlock(&mutex_);
    }

    pthread_mutex_t* GetThreadMutex() {
      return &mutex_;
    }

  private:
    pthread_mutex_t mutex_;
    pid_t holder_;
  };

  class GuardMutex : NonCopyable {
  public:
    explicit GuardMutex(MutexLock& mutex)
        : mutex_(mutex)
    {
      mutex_.Lock();
    }

    ~GuardMutex() {
      mutex_.Unlock();
    }

  private:
    MutexLock& mutex_;
  };
}

#endif //FAKE_THREAD_MUTEX_H

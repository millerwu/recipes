//
// Created by wu on 17-8-14.
//

#ifndef FAKE_THREAD_CONDITION_H
#define FAKE_THREAD_CONDITION_H

#include "NonCopyable.h"
#include "Mutex.h"

namespace fake {
  class Condition : NonCopyable
  {
  public:
    Condition(MutexLock& mutex) :
        mutex_(mutex)
    {
      pthread_cond_init(&cond_, NULL);
    }

    ~Condition() {
      pthread_cond_destroy(&cond_);
    }

    void Wait() {
      pthread_cond_wait(&cond_, mutex_.GetThreadMutex());
    }

    bool WaitForSeconds(int seconds) { // just support second ? improve it
      struct timespec abstime;
      clock_gettime(CLOCK_REALTIME, &abstime);
      abstime.tv_sec += seconds;
      return ETIMEDOUT==pthread_cond_timedwait(&cond_, mutex_.GetThreadMutex(), &abstime);
    }

    void Notify() {
      pthread_cond_signal(&cond_);
    }

    void NotifyAll() {
      pthread_cond_broadcast(&cond_);
    }

  private:
    pthread_cond_t cond_;
    MutexLock& mutex_;
  };
}

#endif //FAKE_THREAD_CONDITION_H

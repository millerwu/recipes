//
// Created by wu on 17-8-24.
//

#ifndef FAKE_BASE_COUNTDOWNLATCH_H
#define FAKE_BASE_COUNTDOWNLATCH_H

#include "NonCopyable.h"
#include "Mutex.h"
#include "Condition.h"

namespace fake {
  class CountDownLatch : NonCopyable
  {
  public:
    explicit CountDownLatch(int count)
      : count_(count),
        mutex_(),
        cond_(mutex_)
    {

    }

    void Wait();
    void CountDown();

    int GetSize() const { return count_; }

  private:
    int count_;
    MutexLock mutex_;
    Condition cond_;
  };
}

#endif //FAKE_BASE_COUNTDOWNLATCH_H

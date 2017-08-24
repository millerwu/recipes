//
// Created by wu on 17-8-24.
//

#include "CountDownLatch.h"


using namespace fake;

void CountDownLatch::Wait()
{
  GuardMutex lock(mutex_);
  if (count_ > 0) {
    cond_.Wait();
  }
}

void CountDownLatch::CountDown()
{
  GuardMutex lock(mutex_);
  --count_;
  if (count_ == 0) {
    cond_.NotifyAll();
  }
}

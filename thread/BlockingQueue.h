//
// Created by wu on 17-8-22.
//

#ifndef FAKE_THREAD_BLOCKINGQUEUE_H
#define FAKE_THREAD_BLOCKINGQUEUE_H

#include <vector>
#include "Mutex.h"
#include "Condition.h"

using namespace std;

namespace fake {
  template <typename T>
  class BlockingQueue : NonCopyable {
  public:
    BlockingQueue()
      : mutex_(),
        cond_(mutex_),
        queue_()
    {

    }

    ~BlockingQueue()
    {

    }

    T Take() {
      GuardMutex lock(mutex_);
      if (Empty()) {
        cond_.Wait();
      }
      T t = queue_.front();
      queue_.erase(queue_.begin());
      return t;
    }

    void Push(T& t) {
      GuardMutex lock(mutex_);
      queue_.push_back(t);
      cond_.Notify();
    }

    int Size() {
      return queue_.size();
    }

    bool Empty() {
      return queue_.empty();
    }
  private:
    vector<T> queue_;
    mutable MutexLock mutex_;
    Condition cond_;
  };
}

#endif //FAKE_THREAD_BLOCKINGQUEUE_H

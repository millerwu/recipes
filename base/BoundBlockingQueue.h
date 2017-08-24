//
// Created by wu on 17-8-23.
//

#ifndef FAKE_BASE_BOUNDBLOCKINGQUEUE_H
#define FAKE_BASE_BOUNDBLOCKINGQUEUE_H

#include "NonCopyable.h"
#include "Condition.h"
#include <vector>

namespace fake
{
  template <typename T>
  class BoundBlockingQueue : NonCopyable
  {
  public:
    explicit BoundBlockingQueue(int max_size)
       : max_size_(max_size),
         queue_(),
         mutex_(),
         empty_cond_(mutex_),
         full_cond_(mutex_)
    {

    }

    ~BoundBlockingQueue()
    {

    }

    T Take()
    {
      GuardMutex lock(mutex_);
      if (Empty()) {
        empty_cond_.Wait();
      }
      assert(!Empty());
      T t(queue_.front());
      queue_.erase(queue_.begin());
      full_cond_.Notify();
      return t;
    }


    void Push(const T& t)
    {
      GuardMutex lock(mutex_);
      if (Full()) {
        full_cond_.Wait();
      }
      assert(!Full());
      queue_.push_back(t);
      empty_cond_.Notify();
    }

    int Size() const
    {
      GuardMutex lock(mutex_);
      return queue_.size();
    }
    bool Full() const
    {
      GuardMutex lock(mutex_);
      return max_size_==queue_.size();
    }
    bool Empty() const
    {
      GuardMutex lock(mutex_);
      return queue_.size()==0;
    }

  private:
    int max_size_;
    std::vector<T> queue_;
    mutable MutexLock mutex_;
    Condition empty_cond_;
    Condition full_cond_;
  };
}

#endif //FAKE_BASE_BOUNDBLOCKINGQUEUE_H

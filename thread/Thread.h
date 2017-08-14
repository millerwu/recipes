//
// Created by Wu on 2017/8/14.
//

#ifndef FAKE_THREAD_THREAD_H
#define FAKE_THREAD_THREAD_H

#include "NonCopyable.h"
#include <pthread.h>

namespace fake
{
  class Thread : NonCopyable {
  public:
    explicit Thread()
        : pid_(0),
          started_(false),
          joined_(false)
    {

    }

    ~Thread() {

    }

    bool Start();
    bool Join();

    bool started() { return started_; }
    bool joined() {return joined_; }

  private:
    pid_t pid_;
    bool started_;
    bool joined_;
  };
}

#endif //FAKE_THREAD_THREAD_H

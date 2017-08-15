//
// Created by Wu on 2017/8/14.
//

#ifndef FAKE_THREAD_THREAD_H
#define FAKE_THREAD_THREAD_H

#include "NonCopyable.h"
#include <pthread.h>
#include <assert.h>
#include <string>
#include <memory>

namespace fake
{
  typedef void (*ThreadFunc)(void);

  class Thread : NonCopyable {
  public:
    explicit Thread(const ThreadFunc& func, const std::string& name = std::string())
        : pid_(new pid_t(0)),
          started_(false),
          joined_(false),
          name_(name),
          func_(func),
          thread_t_(0)
    {

    }

    ~Thread()
    {
      if (started_ && !joined_) {
        pthread_detach(thread_t_);
      }
    }

    bool Start();
    bool Join();

    bool started() const { return started_; }
    pid_t tid() const { return *pid_; }


  private:
    std::shared_ptr<pid_t> pid_;
    bool started_;
    bool joined_;
    std::string name_;
    ThreadFunc func_;
    pthread_t thread_t_;
  };
}

#endif //FAKE_THREAD_THREAD_H

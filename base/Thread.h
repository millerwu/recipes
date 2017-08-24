//
// Created by Wu on 2017/8/14.
//

#ifndef FAKE_BASE_THREAD_H
#define FAKE_BASE_THREAD_H

#include "NonCopyable.h"

#include <pthread.h>
#include <assert.h>
#include <string>
#include <memory>

namespace fake
{
  typedef void (*ThreadFunc)(void*);

  class Thread : NonCopyable {
  public:
    explicit Thread(const ThreadFunc func, void* arg,const std::string& name = std::string())
        : pid_(new pid_t(0)),
          started_(false),
          joined_(false),
          name_(name),
          func_(func),
          thread_t_(0),
          arg_(arg)
    {
      numCreateded_++;
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
    std::string name() const { return name_; }
    static unsigned numCreated() { return numCreateded_; }


  private:
    std::shared_ptr<pid_t> pid_;
    bool started_;
    bool joined_;
    std::string name_;
    ThreadFunc func_;
    pthread_t thread_t_;
    void* arg_;
    static unsigned numCreateded_; // use Atom?
  };

  namespace CurrentThread
  {
    pid_t tid();
    bool isMainThread();
  }
}

#endif //FAKE_BASE_THREAD_H

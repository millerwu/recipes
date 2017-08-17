

#include "Thread.h"
#include <sys/prctl.h>
#include "CurrentThread.h"

namespace fake {
  struct  ThreadData {
    ThreadData(const ThreadFunc& func, void* arg, const std::string& name, const std::shared_ptr<pid_t>& pid) :
        func_(func),
        name_(name),
        wkpid_(pid),
        arg_(arg)
    {

    }

    void RunInThread() {
      pid_t pid = CurrentThread::tid();
      std::shared_ptr<pid_t> sp_pid = wkpid_.lock();

      if (sp_pid) {
        *sp_pid = pid;
        sp_pid.reset(); // this is for decrease the reference in this function
      }

      CurrentThread::t_threadName = name_.empty() ? "FakeThread" : name_.c_str();
      ::prctl(PR_SET_NAME, CurrentThread::t_threadName);
      func_(arg_);
    }

  private:
    ThreadFunc func_;
    std::string name_;
    std::weak_ptr<pid_t > wkpid_;
    void* arg_;
  };

  void* StartThread(void* obj)
  {
    ThreadData* data = static_cast<ThreadData*>(obj);
    data->RunInThread();
    delete data;
    return NULL;
  }

}

using namespace fake;

unsigned Thread::numCreateded_;

bool Thread::Start()
{
  assert(!started_);
  started_ = true;

  ThreadData* data = new ThreadData(func_, arg_,  name_, pid_);
  if (0 != pthread_create(&thread_t_, NULL, StartThread, data) ) {
    started_ = false;
    delete data;
    abort();
  }
}

bool Thread::Join()
{
  assert(started_);
  assert(!joined_);
  joined_ = true;
  pthread_join(thread_t_, NULL);
}
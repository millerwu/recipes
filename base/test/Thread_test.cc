//
// Created by wu on 17-8-15.
//

#include <zconf.h>
#include "../Thread.h"
#include "iostream"

using namespace std;

void ThreadFunc1(void*)
{
  cout << "ThreadFunc1 tid = " << fake::CurrentThread::tid() << endl;
}

void ThreadFunc2(void*)
{
  cout << "ThreadFunc2 tid = " << fake::CurrentThread::tid() << endl;
  sleep(1);
}

class foo
{
public:
  static void ThreadFunc(void* arg)
  {
    cout << "foo ThreadFunc tid = " << fake::CurrentThread::tid() << endl;
    foo* f = static_cast<foo*>(arg);
    f->RunInThread();

  }

  void RunInThread()
  {
    cout << " Run in Thread" << endl;
  }
};

int main()
{
  cout << "pid = " << ::getpid() << " tid = " << fake::CurrentThread::tid() << endl;

  fake::Thread t1(ThreadFunc1, NULL, "thread1");
  t1.Start();
  cout << "t1 name = " << t1.name() << endl;
  t1.Join();

  foo f;
  fake::Thread t2(foo::ThreadFunc, &f, "ThreadFunc");
  t2.Start();
  cout << " t2 name = " << t2.name() << endl;
  t2.Join();

  {
    fake::Thread t3(ThreadFunc2, NULL, "Thread2");
    t3.Start();
  }
  cout << "total Thread number = " << fake::Thread::numCreated() << endl;
  cout << "main out " << endl;

}


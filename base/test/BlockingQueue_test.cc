//
// Created by wu on 17-8-22.
//


#include "../BlockingQueue.h"
#include "../Thread.h"

using namespace fake;

BlockingQueue<int> queue;
bool thead_runing = false;
int count = 0;
int count2 = 0;

void ThreadFunc1(void*)
{
  while (thead_runing) {
    queue.Push(count);
    count++;
  }
}

void ThreadFunc2(void*)
{
  while (thead_runing) {
    queue.Push(count2);
    count2 += 2;
  }
}

int main()
{
  thead_runing = true;
  Thread t1(ThreadFunc1, NULL);
  t1.Start();

  Thread t2(ThreadFunc2, NULL);
  t2.Start();
  int time = 0;

  while(time < 1000) {
    printf("take = %d \n", queue.Take());
    time++;
  }
  thead_runing = false;
  t1.Join();
  t2.Join();
}

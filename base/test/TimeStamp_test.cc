//
// Created by wu on 17-8-21.
//

#include <vector>
#include "../TimeStamp.h"

using namespace fake;

void PassByValue(TimeStamp t)
{
  printf("Value: %s \n", t.ToString().c_str());
}

void PassByReference(TimeStamp& t)
{
  printf("Reference: %s \n", t.ToString().c_str());
}

void Benchmark()
{
  const int kNumber = 1000*1000;

  std::vector<TimeStamp> stamps;
  stamps.reserve(kNumber);
  for (int i = 0; i < kNumber; ++i) {
    stamps.push_back(TimeStamp::Now());
  }
  printf("%s \n", stamps.front().ToString().c_str());
  printf("%s \n", stamps.back().ToString().c_str());
  printf("%f \n", TimeDiff(stamps.back(), stamps.front()));
  return;
}


int main()
{
  TimeStamp now(TimeStamp::Now());
  printf("%s \n", now.ToString().c_str());
  printf("%s \n", now.ToFormattedString().c_str());

  PassByReference(now);
  PassByValue(now);

  Benchmark();

  return 0;
}
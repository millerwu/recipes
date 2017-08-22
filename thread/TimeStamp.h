//
// Created by wu on 17-8-18.
//

#ifndef FAKE_THREAD_TIMESTAMP_H
#define FAKE_THREAD_TIMESTAMP_H

#include "Copyable.h"
#include <string>

using namespace std;

namespace fake {
  class TimeStamp : Copyable{
  public:
    TimeStamp()
      : microSecondsSinceEpoch_(0)
    {

    }

    explicit TimeStamp(int64_t microSeconds)
      : microSecondsSinceEpoch_(microSeconds)
    {

    }

    string ToString() const;
    string ToFormattedString(bool showMicroSeconds = true) const;

    int64_t microSecondsSinceEpoch() const { return microSecondsSinceEpoch_; }

    bool Valid() { return microSecondsSinceEpoch_>0; }

    static TimeStamp Now();
    static TimeStamp InValid()
    {
      return TimeStamp();
    }

    static TimeStamp FromUnixTime(time_t t)
    {
      return FromUnixTime(t, 0);
    }

    static TimeStamp FromUnixTime(time_t t, int microSecond)
    {
      return TimeStamp(static_cast<int64_t>(t)*kMicroSecondsPerSecond + microSecond);
    }

    static const int kMicroSecondsPerSecond = 1000 * 1000;

  private:
    int64_t microSecondsSinceEpoch_;
  };

  inline bool operator<(TimeStamp lhs, TimeStamp rhs)
  {
    return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
  }

  inline bool operator>(TimeStamp lhs, TimeStamp rhs)
  {
    return lhs.microSecondsSinceEpoch() > rhs.microSecondsSinceEpoch();
  }

  inline bool operator==(TimeStamp lhs, TimeStamp rhs)
  {
    return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
  }

  inline double TimeDiff(TimeStamp high, TimeStamp low)
  {
    __int64_t diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
    return static_cast<double>(diff) / TimeStamp::kMicroSecondsPerSecond;
  }

  inline TimeStamp AddTime(TimeStamp t, double addTime)
  {
    int64_t time = static_cast<int64_t>(addTime * TimeStamp::kMicroSecondsPerSecond);
    return TimeStamp(t.microSecondsSinceEpoch() + time);
  }

}



#endif //FAKE_THREAD_TIMESTAMP_H

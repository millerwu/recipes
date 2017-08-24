//
// Created by wu on 17-8-18.
//

#include "TimeStamp.h"
#include <inttypes.h>
#include <sys/time.h>

using namespace fake;

string TimeStamp::ToString() const
{
  char buf[32] = {0};
  int64_t seconds = microSecondsSinceEpoch_/kMicroSecondsPerSecond;
  int64_t micro_seconds = microSecondsSinceEpoch_%kMicroSecondsPerSecond;
  snprintf(buf, sizeof(buf)-1, "%" PRId64 ".%06" PRId64 "", seconds, micro_seconds);
  return buf;
}

string TimeStamp::ToFormattedString(bool showMicroSeconds) const
{
  char buf[32] = {0};
  time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_/kMicroSecondsPerSecond);
  struct tm tm_time;
  gmtime_r(&seconds, &tm_time);

  if (showMicroSeconds) {
    int microseconds = microSecondsSinceEpoch_%kMicroSecondsPerSecond;
    snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d",
            tm_time.tm_year+1990, tm_time.tm_mon+1, tm_time.tm_mday,
            tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec, microseconds);
  } else {
    snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d",
             tm_time.tm_year+1990, tm_time.tm_mon+1, tm_time.tm_mday,
             tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
  }
  return buf;
}

TimeStamp TimeStamp::Now()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  int64_t time = tv.tv_sec*kMicroSecondsPerSecond + tv.tv_usec;
  return TimeStamp(time);
}
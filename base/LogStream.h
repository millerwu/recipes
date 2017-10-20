//
// Created by wu on 17-9-21.
//

#ifndef FAKE_BASE_LOGSTREAM_H
#define FAKE_BASE_LOGSTREAM_H

namespace fake
{
  template <int SIZE>
  class FixBuffer : Copyable
  {
  public:
    explicit FixBuffer() :
        cur_(data_)
    {

    }

    ~FixBuffer()
    {

    }

    void append(const char* buffer, int length)
    {
      int copy_length = 0;
      if (SIZE-(cur_-data_) >= length) {
        copy_length = length;
      } else {
        copy_length = SIZE-(cur_-data_);
      }
      memcpy(cur_, buffer, copy_length);
      cur_ += copy_length;
    }

  private:
    char data_[SIZE];
    char* cur_;
  };

  class LogStream : NonCopyable
  {
  public:
    LogStream();
    ~LogStream();


  };
}

#endif //FAKE_BASE_LOGSTREAM_H

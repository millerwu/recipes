//
// Created by wu on 17-9-21.
//

#ifndef FAKE_BASE_LOGSTREAM_H
#define FAKE_BASE_LOGSTREAM_H

namespace fake
{
namespace detail {

  const int kSmallBuffer = 4000;
  const int kLargeBuffer = 4000*1000;

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

    void append(const char* buffer, size_t length)
    {
      if (avail()>length) {
        memcpy(cur_, buffer, length);
        cur_ += length;
      }
    }

    const char* data() { return data_; }
    int length() const { return static_cast<int>(cur_-data_); }

    //directly control buffer
    char* current() { return cur_; }
    int avail() const { return static_cast<int>(end()-cur_); }
    void add(int len) { cur_ += len; }

    void reset() { cur_ = data_; }
    void bzero() { ::bzero(data_, sizeof(data_)); }


  private:
    const char* end() { return data_ + sizeof(data_);}
    char data_[SIZE];
    char* cur_;
  };
}
  class LogStream : NonCopyable
  {
    typedef LogStream self;
  public:
    typedef detail::FixBuffer<detail::kSmallBuffer> Buffer;
    self& operator<<(bool v)
    {
      buffer_.append(v ? "1": "0", 1);
      return *this;
    }

  private:
    Buffer buffer_;
    LogStream();
    ~LogStream();
  };

}

#endif //FAKE_BASE_LOGSTREAM_H

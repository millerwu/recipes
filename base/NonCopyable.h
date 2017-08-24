//
// Created by wu on 17-8-14.
//

#ifndef FAKE_BASE_NONCOPYABLE_H
#define FAKE_BASE_NONCOPYABLE_H

namespace fake {
  class NonCopyable{
  protected:
    NonCopyable() { }
    ~NonCopyable() { }

  private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator=(const NonCopyable&);
  };
}

#endif //FAKE_BASE_NONCOPYABLE_H

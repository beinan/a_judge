#pragma once

#ifdef linux
#elif defined __APPLE_CC__
#else

class Thread;

#define NOGDI
#define NOUSER
#undef SIZE

#include <Windows.h>

class WindowsThread {
public:
  WindowsThread();
  ~WindowsThread();
  void start(Thread * this_ref);
  void join();
  static void sleep(int milliseconds);
private:
  HANDLE m_thread;
};

#endif

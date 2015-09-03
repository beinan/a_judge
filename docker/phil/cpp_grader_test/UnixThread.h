#pragma once

class Thread;

#if (defined linux || defined __APPLE_CC__)

#include <pthread.h>

class UnixThread {
public:
  UnixThread();
  void start(Thread * this_ref);
  void join();
  static void sleep(int milliseconds);
private:
  pthread_t m_thread;
};

#endif


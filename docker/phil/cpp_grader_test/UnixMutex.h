#pragma once

#if (defined linux || defined __APPLE_CC__)

#include <pthread.h>

class UnixMutex {
public:
  UnixMutex();
  ~UnixMutex();
  void lock();
  void unlock();
private:
  pthread_mutex_t m_mutex;
};
#endif


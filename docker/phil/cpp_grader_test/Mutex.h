#pragma once

#if (defined linux || defined __APPLE_CC__)
#include "UnixMutex.h"
#else
#include "WindowsMutex.h"
#endif

class Mutex {
public:
  void lock();
  void unlock();
private:
  
#if (defined linux || defined __APPLE_CC__)
  UnixMutex m_base;
#else
  WindowsMutex m_base;
#endif

};
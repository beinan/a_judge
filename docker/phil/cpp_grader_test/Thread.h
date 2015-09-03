#pragma once

#if (defined linux || defined __APPLE_CC__)
#include "UnixThread.h"
#else
#include "WindowsThread.h"
#endif

class Thread { 
public:
  void start();
  void join();
  virtual void run() = 0;
  static size_t numCores();
  static void sleep(int milliseconds);
private:

#if (defined linux || defined __APPLE_CC__)
  UnixThread m_base;
#else
  WindowsThread m_base;
#endif  

};

#ifndef STOPWATCH_H
#define STOPWATCH_H

#if (defined linux || defined __APPLE_CC__)
#include "UnixStopwatch.h"
#else
#include "WindowsStopwatch.h"
#endif

class Stopwatch {
public:
  Stopwatch();
  void start();
  void stop();
  void pause();
  void unpause();
  long getTime();
private:
#if (defined linux || defined __APPLE_CC__)
  UnixStopwatch m_Base;
#else
  WindowsStopwatch m_Base;
#endif

  long m_total; 
};
#endif


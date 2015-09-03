//
// revision history:
//
// version 1.0 - intial release
//
// version 1.1 - fix by Shawn Mueller to start the stopwatch in the constructor
//               to give similar behaviour to the unix stopwatch.
//
#include "WindowsStopwatch.h"
#include <exception>

#ifdef linux
#elif defined __APPLE_CC__
#else

WindowsStopwatch::WindowsStopwatch(){
  b = 0UL;
  if ( QueryPerformanceFrequency((LARGE_INTEGER*)&f) == 0) 
    throw std::exception("no high resolution counter on this platform");

  QueryPerformanceCounter((LARGE_INTEGER*)&a);
}

void WindowsStopwatch::start(){
  ::Sleep(0);
  QueryPerformanceCounter((LARGE_INTEGER*)&a);
}

void WindowsStopwatch::stop(){
  QueryPerformanceCounter((LARGE_INTEGER*)&b);
}

long WindowsStopwatch::getTime(){
  __int64 d = (b-a); 
  __int64 ret_milliseconds;
  ret_milliseconds = (d*1000UL)/f; 
  return ret_milliseconds;
}

#endif

#pragma once

//help from Dr. Fawcett:
//http://www.lcs.syr.edu/faculty/fawcett/handouts/coretechnologies/ThreadsAndSynchronization/code/Threads/locks.h
//http://www.lcs.syr.edu/faculty/fawcett/handouts/coretechnologies/ThreadsAndSynchronization/code/Threads/locks.cpp

#ifdef linux
#elif defined __APPLE_CC__
#else

#include <Windows.h>

class WindowsMutex {
public:
  WindowsMutex();
  ~WindowsMutex();
  void lock();
  void unlock();
private:
  CRITICAL_SECTION m_section;
};

#endif
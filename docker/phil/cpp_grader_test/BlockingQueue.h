#pragma once

#if (defined linux || defined __APPLE_CC__)
#include "UnixBlockingQueue.h"
#else
#include "WindowsBlockingQueue.h"
#endif

template<typename T>
class BlockingQueue {
public:
  void push_back(T value);
  T pop_front();
private:
#if (defined linux || defined __APPLE_CC__)
  UnixBlockingQueue<T> m_base;
#else
  WindowsBlockingQueue<T> m_base;
#endif

};

template<typename T>
void BlockingQueue<T>::push_back(T value)
{
  m_base.push_back(value);
}

template<typename T>
T BlockingQueue<T>::pop_front() 
{
  return m_base.pop_front();
}





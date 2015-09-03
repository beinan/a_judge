#pragma once

#ifdef linux
#elif defined __APPLE_CC__
#else

#include <deque>
#include <iostream>
#include <Windows.h>
#include "Mutex.h"

//help thanks to Dr. Fawcett: 
//http://www.lcs.syr.edu/faculty/fawcett/handouts/coretechnologies/ThreadsAndSynchronization/code/BlockingQueue/BlockingQueue.h

template <typename T>
class WindowsBlockingQueue {
public:
  WindowsBlockingQueue();
  ~WindowsBlockingQueue();
  void push_back(T value);
  T pop_front();
private:
  std::deque<T> m_queue;  
  HANDLE m_event;
  Mutex m_mutex;
};

template <typename T>
WindowsBlockingQueue<T>::WindowsBlockingQueue()
{
  m_event = CreateEvent(0,FALSE,TRUE,0);
}

template <typename T>
WindowsBlockingQueue<T>::~WindowsBlockingQueue()
{
  CloseHandle(m_event);
}

template <typename T>
void WindowsBlockingQueue<T>::push_back(T value)
{
  m_mutex.lock();
  m_queue.push_back(value);
  SetEvent(m_event);
  m_mutex.unlock();
}

template <typename T>
T WindowsBlockingQueue<T>::pop_front()
{
  T ret;
  bool found = false;
  while(true){
    m_mutex.lock();
    if(m_queue.empty() == false){
      ret = m_queue.front();
      m_queue.pop_front();
      m_mutex.unlock();
      break;
    } else {
      ResetEvent(m_event);
      m_mutex.unlock();
      WaitForSingleObject(m_event,INFINITE);
    }
  }
  return ret;
}

#endif
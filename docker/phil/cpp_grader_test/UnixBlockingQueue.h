#pragma once

#if (defined linux || defined __APPLE_CC__)

#include <pthread.h>
#include <deque>
#include <iostream>

template <typename T>
class UnixBlockingQueue {
public:
  UnixBlockingQueue();
  ~UnixBlockingQueue();
  void push_back(T value);
  T pop_front();
private:
  pthread_mutex_t m_mutex;
  pthread_cond_t m_cond;
  std::deque<T> m_queue;  
};

template <typename T>
UnixBlockingQueue<T>::UnixBlockingQueue()
{
  pthread_mutex_init(&m_mutex, NULL);
  pthread_cond_init(&m_cond, NULL);
}

template <typename T>
UnixBlockingQueue<T>::~UnixBlockingQueue()
{
  pthread_mutex_destroy(&m_mutex);
  pthread_cond_destroy(&m_cond);
}

template <typename T>
void UnixBlockingQueue<T>::push_back(T value)
{
  pthread_mutex_lock(&m_mutex);
  m_queue.push_back(value);
  pthread_cond_signal(&m_cond);
  pthread_mutex_unlock(&m_mutex);
}

template <typename T>
T UnixBlockingQueue<T>::pop_front()
{
  T ret;
  bool found = false;
  while(true){
    pthread_mutex_lock(&m_mutex);
    if(m_queue.empty()){
      pthread_cond_wait(&m_cond, &m_mutex);
    } else {
      ret = m_queue.front();
      m_queue.pop_front();
      found = true;
    }
    pthread_mutex_unlock(&m_mutex);
    if(found){
      return ret;
    }
  }
}

#endif
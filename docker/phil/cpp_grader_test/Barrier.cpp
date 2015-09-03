#include "Barrier.h"
#include "Thread.h"

Barrier::Barrier()
  : m_count(0), m_count2(0), m_count3(0)
{
}

void Barrier::wait()
{
  m_mutex.lock();
  m_count2 = 0;
  m_count++;
  m_mutex.unlock();

  while(true){
    m_mutex.lock();
    volatile int count = m_count;
    m_mutex.unlock();
    
    if(count == (int) Thread::numCores()){
      break;
    } else {
      Thread::sleep(10);
    }
  }

  m_mutex.lock();
  m_count3 = 0;
  m_count2++;
  m_mutex.unlock();

  while(true){
    m_mutex.lock();
    volatile int count = m_count2;
    m_mutex.unlock();
    
    if(count == (int) Thread::numCores()){
      break;
    } else {
      Thread::sleep(10);
    }
  }

  m_mutex.lock();
  m_count = 0;
  m_count3++;
  m_mutex.unlock();

  while(true){
    m_mutex.lock();
    volatile int count = m_count3;
    m_mutex.unlock();
    
    if(count == (int) Thread::numCores()){
      break;
    } else {
      Thread::sleep(10);
    }
  }
}

#include "Mutex.h"

void Mutex::lock()
{
  m_base.lock();
}

void Mutex::unlock()
{
  m_base.unlock();
}
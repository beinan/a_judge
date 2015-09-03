#pragma once

#include "Mutex.h"

class Barrier {
public:
  Barrier();
  void wait();
private:
  Mutex m_mutex;
  volatile int m_count;
  volatile int m_count2;
  volatile int m_count3;
};

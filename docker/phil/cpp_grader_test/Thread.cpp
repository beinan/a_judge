#include "Thread.h"

void Thread::start()
{
  m_base.start(this);
}

void Thread::join()
{
  m_base.join();
}

size_t Thread::numCores()
{
  return 4;
}

void Thread::sleep(int milliseconds)
{
#if (defined linux || defined __APPLE_CC__)
  UnixThread::sleep(milliseconds);
#else
  WindowsThread::sleep(milliseconds);
#endif  
}

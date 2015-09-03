#include "UnixThread.h"
#include "Thread.h"

#if (defined linux || defined __APPLE_CC__)

#include <unistd.h>

void * thread_fun(void * data)
{
  Thread * thread = (Thread *) data;
  thread->run();
  return NULL;
}

UnixThread::UnixThread()
{
}

void UnixThread::start(Thread * this_ref)
{
  pthread_create(&m_thread, NULL, &thread_fun, this_ref);
}
  
void UnixThread::join()
{
  pthread_join(m_thread, NULL);
}

void UnixThread::sleep(int milliseconds)
{
  usleep(milliseconds*1000);
}

#endif


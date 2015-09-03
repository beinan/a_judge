
#ifdef linux
#elif defined __APPLE_CC__
#else

#include "WindowsThread.h"
#include "Thread.h"

WindowsThread::WindowsThread()
  : m_thread(NULL)
{

}
 
WindowsThread::~WindowsThread()
{
  if(m_thread != NULL){
    CloseHandle(m_thread);
  }
}

DWORD WINAPI threadProc(void * data)
{
  Thread * thread = (Thread *) data;
  thread->run();
  return NULL;
}

void WindowsThread::start(Thread * this_ref)
{
  m_thread = CreateThread(NULL, 0, &threadProc, this_ref, 0, NULL);
}

void WindowsThread::join()
{
  WaitForSingleObject(m_thread, INFINITE);
}

void WindowsThread::sleep(int milliseconds)
{
  Sleep(milliseconds);
}

#endif

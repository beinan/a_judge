#ifdef linux
#elif defined __APPLE_CC__
#else

#include "WindowsMutex.h"

WindowsMutex::WindowsMutex()
{
  InitializeCriticalSection(&m_section);
}
 
WindowsMutex::~WindowsMutex()
{
  DeleteCriticalSection(&m_section);
}
 
void WindowsMutex::lock()
{
  EnterCriticalSection(&m_section);
}

void WindowsMutex::unlock()
{
  LeaveCriticalSection(&m_section);
}

#endif
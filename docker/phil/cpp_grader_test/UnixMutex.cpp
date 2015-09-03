#if (defined linux || defined __APPLE_CC__) 

#include "UnixMutex.h"

UnixMutex::UnixMutex()
{
  pthread_mutex_init(&m_mutex, NULL);
}
  
UnixMutex::~UnixMutex()
{
  pthread_mutex_destroy(&m_mutex);
}

void UnixMutex::lock()
{
  pthread_mutex_lock(&m_mutex);
}

void UnixMutex::unlock()
{
  pthread_mutex_unlock(&m_mutex);
}

#endif


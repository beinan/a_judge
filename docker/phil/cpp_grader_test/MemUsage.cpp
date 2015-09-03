#include "MemUsage.h"
#include <sstream>
#include <iostream>

MemUsage::MemUsage()
{
  m_beginSize = getCurrentRSS() / 1024;
}

//http://stackoverflow.com/questions/669438/how-to-get-memory-usage-at-run-time-in-c
size_t MemUsage::getUsage( )
{
  size_t current_size = getCurrentRSS() / 1024;
  return current_size - m_beginSize;
}

std::string MemUsage::toString(int value)
{
  std::stringstream ss;
  ss << value;

  std::string ret;
  ss >> ret;
  
 return ret;
}

size_t MemUsage::getCurrentRSS()
{
#if defined(_WIN32)
    /* Windows -------------------------------------------------- */
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo( GetCurrentProcess( ), &info, sizeof(info) );
    return (size_t)info.WorkingSetSize;

#elif defined(__APPLE__) && defined(__MACH__)
    /* OSX ------------------------------------------------------ */
    struct mach_task_basic_info info;
    mach_msg_type_number_t infoCount = MACH_TASK_BASIC_INFO_COUNT;
    if ( task_info( mach_task_self( ), MACH_TASK_BASIC_INFO,
        (task_info_t)&info, &infoCount ) != KERN_SUCCESS )
        return (size_t)0L;      /* Can't access? */
    return (size_t)info.resident_size;

#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
    /* Linux ---------------------------------------------------- */
    long rss = 0L;
    FILE* fp = NULL;
    std::string statm_filename = std::string("/proc/") + toString(getpid()) + std::string("/statm");
    if ( (fp = fopen(statm_filename.c_str(), "r" )) == NULL ){
      return (size_t)0L;      /* Can't open? */
    }
    if ( fscanf( fp, "%*s%ld", &rss ) != 1 )
    {
        fclose( fp );
        return (size_t)0L;      /* Can't read? */
    }
    fclose( fp );
    return (size_t)rss * (size_t)sysconf( _SC_PAGESIZE);

#else
    /* AIX, BSD, Solaris, and Unknown OS ------------------------ */
    return (size_t)0L;          /* Unsupported. */
#endif
}

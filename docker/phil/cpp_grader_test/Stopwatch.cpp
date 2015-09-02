#include "Stopwatch.h"

Stopwatch::Stopwatch()
 : m_total(0)
{
  m_Base.start();
}

void Stopwatch::start(){
  m_Base.start();
}

void Stopwatch::stop(){
  m_Base.stop();
}

long Stopwatch::getTime(){
  return m_total + m_Base.getTime();
}

void Stopwatch::pause()
{
  m_Base.stop();
  m_total += m_Base.getTime();
}

void Stopwatch::unpause()
{
  m_Base.start();
}

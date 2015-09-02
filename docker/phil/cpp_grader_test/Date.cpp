#include "Date.h"
#include <sstream>

Date::Date(int month, int day, int year)
  : m_year(year), m_month(month), m_day(day)
{
}

std::string Date::toXmlString()
{
  std::string ret;
  std::ostringstream oss;
  oss << "<year>" << m_year << "</year><month>" << m_month;
  oss << "</month><day>" << m_day << "</day>";
  return oss.str();
}

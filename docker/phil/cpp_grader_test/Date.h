#pragma once

#include <string>

class Date {
public:
  Date(int month, int day, int year);
  std::string toXmlString();
private:  
  int m_year;
  int m_month;
  int m_day;
};

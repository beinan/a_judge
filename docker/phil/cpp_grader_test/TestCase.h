#ifndef TEST_CASE_H
#define TEST_CASE_H

#include <string>

class TestCase {
public:
  bool passed;
  std::string error_message;
  long long time;
};
#endif

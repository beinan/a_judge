#ifndef TO_STRING
#define TO_STRING

#include <string>
#include <sstream>

template <typename T>
std::string toString(T value){
  std::ostringstream oss;
  oss << value;
  return oss.str();
}

#endif

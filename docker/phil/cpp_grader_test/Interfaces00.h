#pragma once

#include <string>

struct IStringEcho {
  IStringEcho() {}
  virtual ~IStringEcho() {}
  virtual std::string echo(std::string input) = 0;
};

struct IStringReverse {
  IStringReverse() {}
  virtual ~IStringReverse() {}
  virtual std::string reverse(std::string input) = 0;
};

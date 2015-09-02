#ifndef GRADER_00_H
#define GRADER_00_H

#include "AbstractGrader.h"
#include "Interfaces00.h"
#include <vector>
#include <string>

class Grader00 : public AbstractGrader {
public:
  virtual int size();
  virtual std::string getDescription(int test_case);
  virtual int getPoints(int test_case);
  virtual Date getDueDate();
  virtual TestCase * grade(int index);
private:
  TestCase * testEcho(std::string input, std::string output);
  TestCase * testReverse(std::string input, std::string output);
};

#endif


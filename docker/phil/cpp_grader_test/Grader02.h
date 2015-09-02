#pragma once

#include "Interfaces02.h"
#include "AbstractGrader.h"
#include "Date.h"
#include <vector>
#include <string>
#include "Random.h"

class Grader02;

typedef TestCase* (Grader02::*TestFunc)(int);

struct TestCaseInfo {
  int point;
  std::string description;
  std::string test_file;
  TestFunc test_func;
};

class Grader02 : public AbstractGrader {
public:
  virtual int size();
  virtual std::string getDescription(int test_case);
  virtual int getPoints(int test_case);
  virtual Date getDueDate();
  virtual TestCase * grade(int index);
private:
  TestCase * testWorkload1(int test_case);
  TestCase * testWorkload2(int test_case);
  TestCase * testWorkload3(int test_case);

  void loadVector(std::ifstream& fin, std::vector<int>& vec);
  bool loadVectors(const std::string& file_name,
                   std::vector<int>& input,
                   std::vector<int>& sorted);

  static const int kTestCasesSize = 14;
  static const TestCaseInfo kTestCases[kTestCasesSize];
};

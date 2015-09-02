#ifndef GRADER_01_H
#define GRADER_01_H

#include "AbstractGrader.h"
#include "Interfaces01.h"
#include "Random.h"
#include <vector>
#include <string>

class Grader01;

typedef TestCase* (Grader01::*TestFunc)(int);

struct TestCaseInfo {
  int point;
  std::string description;
  std::string test_file;
  TestFunc test_func;
};

class Grader01 : public AbstractGrader {
public:
  virtual int size();
  virtual std::string getDescription(int test_case);
  virtual int getPoints(int test_case);
  virtual Date getDueDate();
  virtual TestCase * grade(int index);
private:
  TestCase * singleOrderSort2(int test_case);
  TestCase * singleOrderSort3(int test_case);
  TestCase * singleSequenceOrderSort(int test_case);
  TestCase * singleReverse(int test_case);

  TestCase * doubleOrderSort2(int test_case);
  TestCase * doubleOrderSort3(int test_case);
  TestCase * doubleSequenceOrderSort(int test_case);
  TestCase * doubleReverse(int test_case);

  bool loadSinglyListVector(const std::string& file_name,
                            std::vector<int>& org_seq,
                            std::vector<int>& order_seq);
  bool loadDoublyListVector(const std::string& file_name,
                            std::vector<int>& random_seq,
                            std::vector<int>& org_seq,
                            std::vector<int>& order_seq);
  void loadVector(std::ifstream& fin, std::vector<int>& vec);


  static const int kTestCasesSize = 20;
  static const TestCaseInfo kTestCases[kTestCasesSize];
};

#endif


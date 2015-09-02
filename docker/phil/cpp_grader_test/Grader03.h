#pragma once

#include "Interfaces03.h"
#include "AbstractGrader.h"
#include "Date.h"
#include <vector>
#include <string>
#include "Random.h"

class Grader03 : public AbstractGrader {
public:
  virtual int size();
  virtual std::string getDescription(int test_case);
  virtual int getPoints(int test_case);
  virtual Date getDueDate();
  virtual TestCase * grade(int index);
private:
  TestCase * testVectorDoubleSort(std::string input_filename, std::string obj_filename);
  TestCase * testLinkedListSort(std::string input_filename);
  TestCase * testRunningMedian(std::string input_filename, std::string output_filename, int window_size);
  
  void genVector(std::vector<int>& vec_start, std::vector<int>& vec_gold, int order, int len);
  IDoubleList03 * createList(std::vector<int>& vec_start);
  TestCase * testHeapSort(int order, int len);
  TestCase * testMergeSort(int order, int len);
  TestCase * testKthMin(int order, int len);

  Random m_Random;
};

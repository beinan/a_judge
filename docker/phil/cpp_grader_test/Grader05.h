#pragma once

#include "Interfaces05.h"
#include "AbstractGrader.h"
#include "Date.h"
#include <vector>
#include <string>
#include <set>
#include "Random.h"
#include "Commands05.h"

class Grader05 : public AbstractGrader {
public:
  virtual int size();
  virtual std::string getDescription(int test_case);
  virtual int getPoints(int test_case);
  virtual Date getDueDate();
  virtual TestCase * grade(int index);
private:
  TestCase * testHashMap(std::string filename, std::string iface);
  TestCase * testHashMapBulk(std::string data_filename, std::string cmds_filename);
};

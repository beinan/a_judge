#pragma once

#include "Interfaces04.h"
#include "AbstractGrader.h"
#include "Date.h"
#include <vector>
#include <string>
#include <set>
#include "Random.h"
#include "Commands04.h"

class Grader04 : public AbstractGrader {
public:
  virtual int size();
  virtual std::string getDescription(int test_case);
  virtual int getPoints(int test_case);
  virtual Date getDueDate();
  virtual TestCase * grade(int index);
private:
  TestCase * testAVLTree(std::string cmds_filename);
  TestCase * testBTree(std::string cmds_filename);

  void inorderTraversal(std::set<int>& rb_tree, std::vector<int>& rb_sorted);
  void inorderTraversal(IAVLTreeNode * curr, std::vector<int>& sorted);
  void inorderBTreeTraversal(IBTreeNode * curr, std::vector<int>& visit_order);
  int calcHeight(IAVLTreeNode * curr);
  int checkBTreeHeight(IBTreeNode * curr);
  int log3(int value);

  Random m_Random;
};

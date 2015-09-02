#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "TestCase.h"
#include "Stopwatch.h"
#include "Interfaces01.h"
#include "Grader01.h"


const TestCaseInfo Grader01::kTestCases[kTestCasesSize] = {
  { 5, "single order sort2 small", "single_ordersort2_small.bin", &Grader01::singleOrderSort2 },
  { 5, "single order sort2 large", "single_ordersort2_large.bin", &Grader01::singleOrderSort2 },
  { 5, "single order sort3 small", "single_ordersort3_small.bin", &Grader01::singleOrderSort3 },
  { 5, "single order sort3 odd", "single_ordersort3_odd.bin", &Grader01::singleOrderSort3 },
  { 5, "single order sort3 large", "single_ordersort3_large.bin", &Grader01::singleOrderSort3 },
  { 5, "single sequence order small", "single_sequencesort_small.bin", &Grader01::singleSequenceOrderSort },
  { 5, "single sequence order odd", "single_sequencesort_odd.bin", &Grader01::singleSequenceOrderSort },
  { 5, "single sequence order large", "single_sequencesort_large.bin", &Grader01::singleSequenceOrderSort },
  { 5, "single reverse small", "single_reverse_small.bin", &Grader01::singleReverse },
  { 5, "single reverse large", "single_reverse_large.bin", &Grader01::singleReverse },
  { 5, "double order sort2 small", "double_ordersort2_small.bin", &Grader01::doubleOrderSort2 },
  { 5, "double order sort2 large", "double_ordersort2_large.bin", &Grader01::doubleOrderSort2 },
  { 5, "double order sort3 small", "double_ordersort3_small.bin", &Grader01::doubleOrderSort3 },
  { 5, "double order sort3 odd", "double_ordersort3_odd.bin", &Grader01::doubleOrderSort3 },
  { 5, "double order sort3 large", "double_ordersort3_large.bin", &Grader01::doubleOrderSort3 },
  { 5, "double sequence order small", "double_sequencesort_small.bin", &Grader01::doubleSequenceOrderSort },
  { 5, "double sequence order odd", "double_sequencesort_odd.bin", &Grader01::doubleSequenceOrderSort },
  { 5, "double sequence order large", "double_sequencesort_large.bin", &Grader01::doubleSequenceOrderSort },
  { 5, "double reverse small", "double_reverse_small.bin", &Grader01::doubleReverse },
  { 5, "double reverse large", "double_reverse_large.bin", &Grader01::doubleReverse },
};

void Grader01::loadVector(std::ifstream& fin, std::vector<int>& vec){
  long long len;
  fin.read((char *)&len, sizeof(long long));

  for (size_t i = 0; i < len; ++i){
    int val;
    fin.read((char *)&val, sizeof(int));
    vec.push_back(val);
  }
}

bool Grader01::loadSinglyListVector(const std::string& file_name,
                                    std::vector<int>& org_seq,
                                    std::vector<int>& order_seq) {
  std::ifstream fin(file_name.c_str(), std::ios::binary);
  if (!fin.good()){
    return false;
  }

  loadVector(fin, org_seq);
  loadVector(fin, order_seq);
  fin.close();

  return true;
}

bool Grader01::loadDoublyListVector(const std::string& file_name,
                                    std::vector<int>& random_seq,
                                    std::vector<int>& org_seq,
                                    std::vector<int>& order_seq){
  std::ifstream fin(file_name.c_str(), std::ios::binary);
  if (!fin.good()){
    return false;
  }

  loadVector(fin, random_seq);
  loadVector(fin, org_seq);
  loadVector(fin, order_seq);
  fin.close();

  return true;
}

TestCase * Grader01::singleOrderSort2(int test_case){
  std::vector<int> org_seq;
  std::vector<int> order_seq;

  bool file_is_open = loadSinglyListVector(kTestCases[test_case].test_file, org_seq, order_seq);
  if (!file_is_open)
    return failed("Cannot open file " + kTestCases[test_case].test_file);

  Stopwatch watch;
  watch.start();

  std::map<ISingleNode *, int> pointers;
  ISingleList * single_list = (ISingleList *) createObject("ISingleList");
  if(single_list == NULL){
    return nullObject("ISingleList");
  }
  for(int i = org_seq.size() - 1; i >= 0; --i){
    int value = org_seq[i];
    single_list->addHead(value);
    ISingleNode * head = single_list->getHead();
    watch.pause();
    pointers[head] = value;

    if(head->getValue() != value){
      return failed("problem with addHead");
    }
    watch.unpause();
  }
  
  single_list->orderSort2();
  watch.stop();

  ISingleNode * curr = single_list->getHead();
  for(int i = 0; i < order_seq.size(); ++i){
    if(curr == NULL){
      return failed("list terminated abruptly");
    }
    int curr_value = curr->getValue();
    if(curr_value != order_seq[i]){
      return failed("order incorrect: [index: "+toString(i)+", given: "+toString(curr_value)+", gold: "+toString(order_seq[i])+"]");
    }
    if(pointers[curr] != curr_value){
      return failed("pointer mismatch");
    }
    curr = curr->getNext();
  }
  
  delete single_list;
  
  return passed(watch.getTime());
}

TestCase * Grader01::singleOrderSort3(int test_case){
  std::vector<int> org_seq;
  std::vector<int> order_seq;

  bool file_is_open = loadSinglyListVector(kTestCases[test_case].test_file, org_seq, order_seq);
  if (!file_is_open)
    return failed("Cannot open file " + kTestCases[test_case].test_file);

  Stopwatch watch;
  watch.start();

  std::map<ISingleNode *, int> pointers;
  ISingleList * single_list = (ISingleList *) createObject("ISingleList");
  if(single_list == NULL){
    return nullObject("ISingleList");
  }
  for(int i = org_seq.size() - 1; i >= 0; --i){
    int value = org_seq[i];
    single_list->addHead(value);
    ISingleNode * head = single_list->getHead();
    watch.pause();
    pointers[head] = value;

    if(head->getValue() != value){
      return failed("problem with addHead");
    }
    watch.unpause();
  }
  
  single_list->orderSort3();
  watch.stop();

  ISingleNode * curr = single_list->getHead();
  for(int i = 0; i < order_seq.size(); ++i){
    if(curr == NULL){
      return failed("list terminated abruptly");
    }
    int curr_value = curr->getValue();
    if(curr_value != order_seq[i]){
      return failed("order incorrect: [index: "+toString(i)+", given: "+toString(curr_value)+", gold: "+toString(order_seq[i])+"]");
    }
    if(pointers[curr] != curr_value){
      return failed("pointer mismatch");
    }
    curr = curr->getNext();
  }
  
  delete single_list;
  
  return passed(watch.getTime());
}

TestCase * Grader01::singleSequenceOrderSort(int test_case){
  std::vector<int> org_seq;
  std::vector<int> order_seq;

  bool file_is_open = loadSinglyListVector(kTestCases[test_case].test_file, org_seq, order_seq);
  if (!file_is_open)
    return failed("Cannot open file " + kTestCases[test_case].test_file);

  Stopwatch watch;
  watch.start();

  std::map<ISingleNode *, int> pointers;
  ISingleList * single_list = (ISingleList *) createObject("ISingleList");
  if(single_list == NULL){
    return nullObject("ISingleList");
  }
  for(int i = org_seq.size() - 1; i >= 0; --i){
    int value = org_seq[i];
    single_list->addHead(value);
    ISingleNode * head = single_list->getHead();
    watch.pause();
    pointers[head] = value;

    if(head->getValue() != value){
      return failed("problem with addHead");
    }
    watch.unpause();
  }
  
  single_list->sequenceOrderSort();
  watch.stop();

  ISingleNode * curr = single_list->getHead();
  for(int i = 0; i < order_seq.size(); ++i){
    if(curr == NULL){
      return failed("list terminated abruptly");
    }
    int curr_value = curr->getValue();
    if(curr_value != order_seq[i]){
      return failed("order incorrect: [index: "+toString(i)+", given: "+toString(curr_value)+", gold: "+toString(order_seq[i])+"]");
    }
    if(pointers[curr] != curr_value){
      return failed("pointer mismatch");
    }
    curr = curr->getNext();
  }
  
  delete single_list;

  return passed(watch.getTime());
}

TestCase * Grader01::singleReverse(int test_case){
  std::vector<int> org_seq;
  std::vector<int> order_seq;

  bool file_is_open = loadSinglyListVector(kTestCases[test_case].test_file, org_seq, order_seq);
  if (!file_is_open)
    return failed("Cannot open file " + kTestCases[test_case].test_file);

  Stopwatch watch;
  watch.start();

  std::map<ISingleNode *, int> pointers;
  ISingleList * single_list = (ISingleList *) createObject("ISingleList");
  if(single_list == NULL){
    return nullObject("ISingleList");
  }
  for(int i = org_seq.size() - 1; i >= 0; --i){
    int value = org_seq[i];
    single_list->addHead(value);
    ISingleNode * head = single_list->getHead();
    watch.pause();
    pointers[head] = value;

    if(head->getValue() != value){
      return failed("problem with addHead");
    }
    watch.unpause();
  }
  
  single_list->reverse();
  watch.stop();

  ISingleNode * curr = single_list->getHead();
  for(int i = 0; i < order_seq.size(); ++i){
    if(curr == NULL){
      return failed("list terminated abruptly");
    }
    int curr_value = curr->getValue();
    if(curr_value != order_seq[i]){
      return failed("order incorrect: [index: "+toString(i)+", given: "+toString(curr_value)+", gold: "+toString(order_seq[i])+"]");
    }
    if(pointers[curr] != curr_value){
      return failed("pointer mismatch");
    }
    curr = curr->getNext();
  }
  
  delete single_list;

  return passed(watch.getTime());
}

TestCase * Grader01::doubleOrderSort2(int test_case){
  std::vector<int> org_seq;
  std::vector<int> random_seq;
  std::vector<int> order_seq;

  bool file_is_open = loadDoublyListVector(kTestCases[test_case].test_file, random_seq, org_seq, order_seq);
  if (!file_is_open)
    return failed("Cannot open file " + kTestCases[test_case].test_file);

  size_t len = random_seq.size();

  Stopwatch watch;
  watch.start();

  IDoubleList * double_list = (IDoubleList *) createObject("IDoubleList");
  if(double_list == NULL){
    return nullObject("IDoubleList");
  }
  for(int i = 0; i < random_seq.size(); ++i){
    int value = random_seq[i];
    double_list->addSorted(value);
  }

  IDoubleNode * curr = double_list->getHead();
  watch.pause();

  std::map<IDoubleNode *, int> pointers;
  std::vector<IDoubleNode *> order;

  while(curr != NULL){
    pointers[curr] = curr->getValue();
    order.push_back(curr);
    curr = curr->getNext();
  }

  if(order.size() != len){
    return failed("forward traversal size incorrect");
  }

  watch.unpause();
  curr = double_list->getTail();
  watch.pause();

  std::vector<IDoubleNode *> rorder;
  while(curr != NULL){
    rorder.push_back(curr);
    curr = curr->getPrev();
  }
 
  if(rorder.size() != len){
    return failed("reverse traversal size incorrect");
  }

  for(int i = 0; i < org_seq.size(); ++i){
    int lhs = org_seq[i];
    int rhs = order[i]->getValue();
    if(lhs != rhs){
      return failed("forward traversal is not sorted");
    }
  }

  for(int i = 0; i < org_seq.size(); ++i){
    int lhs = org_seq[org_seq.size() - 1 - i];
    int rhs = rorder[i]->getValue();    
    if(lhs != rhs){
      return failed("reverse traversal is not sorted");
    }
  }

  order.clear();
  rorder.clear();

  watch.unpause();
  double_list->orderSort2();
  IDoubleNode * head = double_list->getHead();
  IDoubleNode * tail = double_list->getTail();
  watch.pause();

  curr = head;
  while(curr != NULL){
    if(pointers[curr] != curr->getValue()){
      return failed("pointer mismatch");
    }
    order.push_back(curr);
    curr = curr->getNext();
  }

  if(order.size() != len){
    return failed("forward traversal size incorrect #2");
  }

  
  for(int i = 0; i < order_seq.size(); ++i){
    int lhs = order_seq[i];
    int rhs = order[i]->getValue();
    if(lhs != rhs){
      return failed("forward traversal is out of final order");
    }
  }

  curr = tail;
  while(curr != NULL){
    if(pointers[curr] != curr->getValue()){
      return failed("pointer mismatch");
    }
    rorder.push_back(curr);
    curr = curr->getPrev();
  }

  for(int i = 0; i < order_seq.size(); ++i){
    int lhs = order_seq[order_seq.size() - 1 - i];
    int rhs = rorder[i]->getValue();    
    if(lhs != rhs){
      return failed("reverse traversal is out of final order");
    }
  }
  
  delete double_list;

  return passed(watch.getTime());
}

TestCase * Grader01::doubleOrderSort3(int test_case){
  std::vector<int> org_seq;
  std::vector<int> random_seq;
  std::vector<int> order_seq;

  bool file_is_open = loadDoublyListVector(kTestCases[test_case].test_file, random_seq, org_seq, order_seq);
  if (!file_is_open)
    return failed("Cannot open file " + kTestCases[test_case].test_file);

  size_t len = random_seq.size();

  Stopwatch watch;
  watch.start();

  IDoubleList * double_list = (IDoubleList *) createObject("IDoubleList");
  if(double_list == NULL){
    return nullObject("IDoubleList");
  }
  for(int i = 0; i < random_seq.size(); ++i){
    int value = random_seq[i];
    double_list->addSorted(value);
  }

  IDoubleNode * curr = double_list->getHead();
  watch.pause();

  std::map<IDoubleNode *, int> pointers;
  std::vector<IDoubleNode *> order;

  while(curr != NULL){
    pointers[curr] = curr->getValue();
    order.push_back(curr);
    curr = curr->getNext();
  }

  if(order.size() != len){
    return failed("forward traversal size incorrect");
  }

  watch.unpause();
  curr = double_list->getTail();
  watch.pause();

  std::vector<IDoubleNode *> rorder;
  while(curr != NULL){
    rorder.push_back(curr);
    curr = curr->getPrev();
  }
 
  if(rorder.size() != len){
    return failed("reverse traversal size incorrect");
  }

  for(int i = 0; i < org_seq.size(); ++i){
    int lhs = org_seq[i];
    int rhs = order[i]->getValue();
    if(lhs != rhs){
      return failed("forward traversal is not sorted");
    }
  }

  for(int i = 0; i < org_seq.size(); ++i){
    int lhs = org_seq[org_seq.size() - 1 - i];
    int rhs = rorder[i]->getValue();    
    if(lhs != rhs){
      return failed("reverse traversal is not sorted");
    }
  }

  order.clear();
  rorder.clear();

  watch.unpause();
  double_list->orderSort3();
  IDoubleNode * head = double_list->getHead();
  IDoubleNode * tail = double_list->getTail();
  watch.pause();

  curr = head;
  while(curr != NULL){
    if(pointers[curr] != curr->getValue()){
      return failed("pointer mismatch");
    }
    order.push_back(curr);
    curr = curr->getNext();
  }

  if(order.size() != len){
    return failed("forward traversal size incorrect #2");
  }
  
  for(int i = 0; i < order_seq.size(); ++i){
    int lhs = order_seq[i];
    int rhs = order[i]->getValue();
    if(lhs != rhs){
      return failed("forward traversal is out of final order");
    }
  }

  curr = tail;
  while(curr != NULL){
    if(pointers[curr] != curr->getValue()){
      return failed("pointer mismatch");
    }
    rorder.push_back(curr);
    curr = curr->getPrev();
  }

  for(int i = 0; i < order_seq.size(); ++i){
    int lhs = order_seq[order_seq.size() - 1 - i];
    int rhs = rorder[i]->getValue();    
    if(lhs != rhs){
      std::cout << "index: " << i << std::endl;
      std::cout << "lhs: " << lhs << std::endl;
      std::cout << "rhs: " << rhs << std::endl;
      for(int j = 0; j < order_seq.size(); ++j){
        std::cout << "order_seq[" << j << "]: " << order_seq[j] << std::endl; 
      }
      return failed("reverse traversal is out of final order");
    }
  }
  
  delete double_list;

  return passed(watch.getTime());
}

TestCase * Grader01::doubleSequenceOrderSort(int test_case){
  std::vector<int> org_seq;
  std::vector<int> random_seq;
  std::vector<int> order_seq;

  bool file_is_open = loadDoublyListVector(kTestCases[test_case].test_file, random_seq, org_seq, order_seq);
  if (!file_is_open)
    return failed("Cannot open file " + kTestCases[test_case].test_file);

  size_t len = random_seq.size();

  Stopwatch watch;
  watch.start();

  IDoubleList * double_list = (IDoubleList *) createObject("IDoubleList");
  if(double_list == NULL){
    return nullObject("IDoubleList");
  }
  for(int i = 0; i < random_seq.size(); ++i){
    int value = random_seq[i];
    double_list->addSorted(value);
  }

  IDoubleNode * curr = double_list->getHead();
  watch.pause();

  std::map<IDoubleNode *, int> pointers;
  std::vector<IDoubleNode *> order;

  while(curr != NULL){
    pointers[curr] = curr->getValue();
    order.push_back(curr);
    curr = curr->getNext();
  }

  if(order.size() != len){
    return failed("forward traversal size incorrect");
  }

  watch.unpause();
  curr = double_list->getTail();
  watch.pause();

  std::vector<IDoubleNode *> rorder;
  while(curr != NULL){
    rorder.push_back(curr);
    curr = curr->getPrev();
  }
 
  if(rorder.size() != len){
    return failed("reverse traversal size incorrect");
  }

  for(int i = 0; i < org_seq.size(); ++i){
    int lhs = org_seq[i];
    int rhs = order[i]->getValue();
    if(lhs != rhs){
      return failed("forward traversal is not sorted");
    }
  }

  for(int i = 0; i < org_seq.size(); ++i){
    int lhs = org_seq[org_seq.size() - 1 - i];
    int rhs = rorder[i]->getValue();    
    if(lhs != rhs){
      return failed("reverse traversal is not sorted");
    }
  }

  order.clear();
  rorder.clear();

  watch.unpause();
  double_list->sequenceOrderSort();
  IDoubleNode * head = double_list->getHead();
  IDoubleNode * tail = double_list->getTail();
  watch.pause();

  curr = head;
  while(curr != NULL){
    if(pointers[curr] != curr->getValue()){
      return failed("pointer mismatch");
    }
    order.push_back(curr);
    curr = curr->getNext();
  }

  if(order.size() != len){
    return failed("forward traversal size incorrect #2");
  }
  
  for(int i = 0; i < order_seq.size(); ++i){
    int lhs = order_seq[i];
    int rhs = order[i]->getValue();
    if(lhs != rhs){
      return failed("forward traversal is out of final order");
    }
  }

  curr = tail;
  while(curr != NULL){
    if(pointers[curr] != curr->getValue()){
      return failed("pointer mismatch");
    }
    rorder.push_back(curr);
    curr = curr->getPrev();
  }

  for(int i = 0; i < order_seq.size(); ++i){
    int lhs = order_seq[order_seq.size() - 1 - i];
    int rhs = rorder[i]->getValue();    
    if(lhs != rhs){
      return failed("reverse traversal is out of final order");
    }
  }
  
  delete double_list;

  return passed(watch.getTime());
}

TestCase * Grader01::doubleReverse(int test_case){
  std::vector<int> org_seq;
  std::vector<int> random_seq;
  std::vector<int> order_seq;

  bool file_is_open = loadDoublyListVector(kTestCases[test_case].test_file, random_seq, org_seq, order_seq);
  if (!file_is_open)
    return failed("Cannot open file " + kTestCases[test_case].test_file);

  size_t len = random_seq.size();

  Stopwatch watch;
  watch.start();

  IDoubleList * double_list = (IDoubleList *) createObject("IDoubleList");
  if(double_list == NULL){
    return nullObject("IDoubleList");
  }
  for(int i = 0; i < random_seq.size(); ++i){
    int value = random_seq[i];
    double_list->addSorted(value);
  }

  IDoubleNode * curr = double_list->getHead();
  watch.pause();

  std::map<IDoubleNode *, int> pointers;
  std::vector<IDoubleNode *> order;

  while(curr != NULL){
    pointers[curr] = curr->getValue();
    order.push_back(curr);
    curr = curr->getNext();
  }

  if(order.size() != len){
    return failed("forward traversal size incorrect");
  }

  watch.unpause();
  curr = double_list->getTail();
  watch.pause();

  std::vector<IDoubleNode *> rorder;
  while(curr != NULL){
    rorder.push_back(curr);
    curr = curr->getPrev();
  }
 
  if(rorder.size() != len){
    return failed("reverse traversal size incorrect");
  }

  for(int i = 0; i < org_seq.size(); ++i){
    int lhs = org_seq[i];
    int rhs = order[i]->getValue();
    if(lhs != rhs){
      return failed("forward traversal is not sorted");
    }
  }

  for(int i = 0; i < org_seq.size(); ++i){
    int lhs = org_seq[org_seq.size() - 1 - i];
    int rhs = rorder[i]->getValue();    
    if(lhs != rhs){
      return failed("reverse traversal is not sorted");
    }
  }

  order.clear();
  rorder.clear();

  watch.unpause();
  double_list->reverse();
  IDoubleNode * head = double_list->getHead();
  IDoubleNode * tail = double_list->getTail();
  watch.pause();

  curr = head;
  while(curr != NULL){
    if(pointers[curr] != curr->getValue()){
      return failed("pointer mismatch");
    }
    order.push_back(curr);
    curr = curr->getNext();
  }

  if(order.size() != len){
    return failed("forward traversal size incorrect #2");
  }
  
  for(int i = 0; i < order_seq.size(); ++i){
    int lhs = order_seq[i];
    int rhs = order[i]->getValue();
    if(lhs != rhs){
      return failed("forward traversal is out of final order");
    }
  }

  curr = tail;
  while(curr != NULL){
    if(pointers[curr] != curr->getValue()){
      return failed("pointer mismatch");
    }
    rorder.push_back(curr);
    curr = curr->getPrev();
  }

  for(int i = 0; i < order_seq.size(); ++i){
    int lhs = order_seq[order_seq.size() - 1 - i];
    int rhs = rorder[i]->getValue();    
    if(lhs != rhs){
      return failed("reverse traversal is out of final order");
    }
  }
  
  delete double_list;

  return passed(watch.getTime());
}

int Grader01::size(){
  return kTestCasesSize;
}

std::string Grader01::getDescription(int test_case) {
  if (test_case >= size())
    return "";

  return kTestCases[test_case].description;
}

int Grader01::getPoints(int test_case) {
  if (test_case >= size())
    return 0;

  return kTestCases[test_case].point;
}

Date Grader01::getDueDate() {
  return Date(1, 1, 2011);
}

TestCase * Grader01::grade(int index){
  if (index >= size())
    return NULL;

  return (this->*kTestCases[index].test_func)(index);
}

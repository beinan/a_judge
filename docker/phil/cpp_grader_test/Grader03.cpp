#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <iostream>
#include "Interfaces03.h"
#include "TestCase.h"
#include "Stopwatch.h"
#include "Grader03.h"
#include "vector.h"
#include <cmath>
#include <fstream>

TestCase * Grader03::testVectorDoubleSort(std::string input_filename, std::string obj_filename)
{
  std::vector<double> unsorted;
  std::vector<double> sorted;

  loadBinarySequence(input_filename, unsorted);
  sorted = unsorted;

  Stopwatch watch;
  watch.start();
  IVectorDoubleSort * sorter = (IVectorDoubleSort *) createObject(obj_filename);
  if(sorter == NULL){
    return nullObject(obj_filename);
  }
  
  sorter->sort(unsorted);
  watch.stop();

  std::sort(sorted.begin(), sorted.end());

  for(int i = 0; i < sorted.size(); ++i){
    if(sorted[i] != unsorted[i]){
      return failed("sort does not match");
    }
  }

  return passed(watch.getTime());
}
  
TestCase * Grader03::testLinkedListSort(std::string input_filename)
{
  std::vector<double> input_vec;

  loadBinarySequence(input_filename, input_vec);

  std::map<double, LinkedListNode *> pointers;

  LinkedListNode * head;
  LinkedListNode * curr;

  head = new LinkedListNode();
  head->key = input_vec[0];
  pointers[input_vec[0]] = head;
  
  curr = new LinkedListNode();
  curr->key = input_vec[1];
  pointers[input_vec[1]] = curr;

  head->next = curr;

  for(size_t i = 2; i < input_vec.size(); ++i){
    double value = input_vec[i];
    LinkedListNode * next = new LinkedListNode();
    next->key = value;
    next->next = NULL;
    pointers[value] = next;
    curr->next = next;
    curr = next;
  }

  Stopwatch watch;
  watch.start();

  ILinkedListSort * sorter = (ILinkedListSort *) createObject("ILinkedListSort");
  if(sorter == NULL){
    return nullObject("ILinkedListSort");
  }

  LinkedListNode * new_head = sorter->sort(head);
  watch.stop();

  std::sort(input_vec.begin(), input_vec.end());

  curr = new_head;

  for(size_t i = 0; i < input_vec.size(); ++i){
    if(curr == NULL){
      return failed("null curr during iteration");
    }
    double key = curr->key;
    if(pointers[key] != curr){
      return failed("must move pointers and not keys");
    }
    if(key != input_vec[i]){
      return failed("incorrect key");
    }
    curr = curr->next;
  }
  return passed(watch.getTime());
}

TestCase * Grader03::testRunningMedian(std::string input_filename, 
  std::string output_filename, int window_size)
{

  std::vector<int> input_vec;
  std::vector<int> output_vec;

  loadBinarySequence(input_filename, input_vec);
  loadBinarySequence(output_filename, output_vec);

  Stopwatch watch;
  watch.start();

  IRunningMedian * running = (IRunningMedian *) createObject("IRunningMedian");
  if(running == NULL){
    return nullObject("IRunningMedian");
  }

  std::vector<int> user_output = running->compute(input_vec, window_size);
  watch.stop();

  if(vectorEqual(output_vec, user_output) == false){
    return failed("result incorrect"); 
  }

  return passed(watch.getTime());
}

void Grader03::genVector(std::vector<int>& vec_start, std::vector<int>& vec_gold, int order, int len)
{
  if(order == 0){
    for(int i = 0; i < len; ++i){
      vec_start.push_back(i);
    }
  } else if(order == 1){
    for(int i = 0; i < len; ++i){
      vec_start.push_back(len-i);
    }
  } else {
    m_Random.randomVector(len, vec_start);
  }
  for(size_t i = 0; i < vec_start.size(); ++i){
    vec_gold.push_back(vec_start[i]);
  }
  sort(vec_gold.begin(), vec_gold.end());
}

TestCase * Grader03::testHeapSort(int order, int len)
{
  std::vector<int> vec_start;
  std::vector<int> vec_gold;
  genVector(vec_start, vec_gold, order, len);

  IHeapSort * sorter = (IHeapSort *) createObject("IHeapSort");
  if(sorter == NULL){
    return nullObject("IHeapSort");
  }
  Stopwatch watch;
  sorter->sort(vec_start);
  watch.stop();

  TestCase * ret = new TestCase();
  ret->passed = true;
  ret->error_message = "no errors";
  ret->time = watch.getTime();

  if(vec_start.size() != vec_gold.size()){
    ret->passed = false;
    ret->error_message = "vec.size() != ans.size()";
    return ret;
  }

  for(size_t i = 0; i < vec_gold.size(); ++i){
    int lhs = vec_gold[i];
    int rhs = vec_start[i];
    if(lhs != rhs){
      ret->passed = false;
      ret->error_message = std::string("location ") + toString(i) + std::string(" has the first error");
      return ret;
    }
  }

  return ret;
}

TestCase * Grader03::testMergeSort(int order, int len)
{
  std::vector<int> vec_start;
  std::vector<int> vec_gold;
  genVector(vec_start, vec_gold, order, len);

  ICircularList * list = (ICircularList *) createObject("ICircularList");
  if(list == NULL){
    return nullObject("ICircularList");
  }
  
  for(size_t i = 0; i < vec_start.size(); ++i){
    list->addHead(vec_start[i]);
  }

  TestCase * ret = new TestCase();
  ret->passed = true;
  ret->error_message = "no errors";
  ret->time = 0;

  std::map<ISingleNode03 *, int> pointers;
  ISingleNode03 * tail = list->getTail();
  if(tail == NULL){
    ret->passed = false;
    ret->error_message = "getTail cannot be null";
    return ret;
  }
  tail = tail->getNext();

  for(size_t i = 0; i < vec_start.size(); ++i){
    pointers[tail] = tail->getValue();
    tail = tail->getNext();
  }  

  IMergeSort * sorter = (IMergeSort *) createObject("IMergeSort");
  if(sorter == NULL){
    return nullObject("IMergeSort");
  }
  
  Stopwatch watch;
  sorter->mergeSort(list);
  watch.stop();
  ret->time = watch.getTime();

  tail = list->getTail();
  if(tail == NULL){
    ret->passed = false;
    ret->error_message = "getTail cannot be null";
    return ret;
  }

  tail = tail->getNext();
  for(size_t i = 0; i < vec_gold.size(); ++i){
    int lhs = tail->getValue();
    int rhs = vec_gold[i];

    if(lhs != rhs){
      ret->passed = false;
      ret->error_message = std::string("location ") + toString(i) + std::string(" has the first error. your answer is: ") + toString(lhs) + std::string(" , while our answer is: ") + toString(rhs);
      return ret;
    }

    if(!(pointers[tail] == lhs)){
      ret->passed = false;
      ret->error_message = "you must manipulate pointers";
      return ret;
    }

    tail = tail->getNext();
  }  
  return ret;
}

IDoubleList03 * Grader03::createList(std::vector<int>& vec_start)
{
  IDoubleList03 * list = (IDoubleList03 * ) createObject("IDoubleList03");
  if(list == NULL){
    return NULL;
  }
    
  for(size_t j = 0; j < vec_start.size(); ++j){
    list->addBack(vec_start[j]);
  }

  return list;
}

TestCase * Grader03::testKthMin(int order, int len)
{
  std::vector<int> vec_start;
  std::vector<int> vec_gold;
  genVector(vec_start, vec_gold, order, len);

  TestCase * ret = new TestCase();

  Stopwatch watch;
  watch.start();
  watch.pause();

  IKthMin * min = (IKthMin *) createObject("IKthMin");
  if(min == NULL){
    return nullObject("IKthMin");
  }

  for(size_t i = 0; i < vec_gold.size(); ++i){   
    IDoubleList03 * list = createList(vec_start);
    if(list == NULL){
      return nullObject("IDoubleList03");
    }
    watch.unpause(); 
    int kth = min->findKthMin(list, i);
    watch.pause();
    delete list;

    if(kth != vec_gold[i]){
      ret->passed = false;  
      ret->error_message = std::string("the ")+toString(i)+std::string("th min should be: ")+toString(vec_gold[i])+std::string(". you said it was: ")+toString(kth);
      return ret;
    }
  }

  ret->passed = true;
  ret->error_message = "no errors";
  ret->time = watch.getTime();

  return ret;
}

int Grader03::size(){
  return 24;
}

std::string Grader03::getDescription(int test_case)
{
  switch(test_case){
  case 0: return "vector double sort1";
  case 1: return "vector double sort2";
  case 2: return "linked-list sort small";
  case 3: return "linked-list sort large";
  case 4: return "running median small";
  case 5: return "running median large";
  case 6: return "heapsort sorted small";
  case 7: return "heapsort reverse sorted small";
  case 8: return "heapsort random small";
  case 9: return "heapsort sorted big";
  case 10: return "heapsort reverse sorted big";
  case 11: return "heapsort random big";
  case 12: return "mergesort sorted small";
  case 13: return "mergesort reverse sorted small";
  case 14: return "mergesort random sorted small";
  case 15: return "mergesort sorted big";
  case 16: return "mergesort reverse sorted big";
  case 17: return "mergesort random big";
  case 18: return "kth min sorted small";
  case 19: return "kth min reverse sorted small";
  case 20: return "kth min random small";
  case 21: return "kth min sorted big";
  case 22: return "kth min reverse sorted big";
  case 23: return "kth min random big";
  }
  return "";
}

int Grader03::getPoints(int test_case)
{
  switch(test_case){
  case 0: return 5;
  case 1: return 5;
  case 2: return 4;
  case 3: return 5;
  case 4: return 4;
  case 5: return 5;
  case 6: return 4;
  case 7: return 4;
  case 8: return 4;
  case 9: return 4;
  case 10: return 4;
  case 11: return 4;
  case 12: return 4;
  case 13: return 4;
  case 14: return 4;
  case 15: return 4;
  case 16: return 4;
  case 17: return 4;
  case 18: return 4;
  case 19: return 4;
  case 20: return 4;
  case 21: return 4;
  case 22: return 4;
  case 23: return 4;
  }
  return 0;
}

Date Grader03::getDueDate()
{
  return Date(1, 1, 2011);
}
  
TestCase * Grader03::grade(int index){
  switch(index){
  case 0:
    return testVectorDoubleSort("workload1.bin", "IVectorDoubleSort1");
  case 1:
    return testVectorDoubleSort("workload2.bin", "IVectorDoubleSort2");
  case 2:
    return testLinkedListSort("linked_list_input_small.bin");
  case 3:
    return testLinkedListSort("linked_list_input_large.bin");
  case 4:
    return testRunningMedian("median_input_small.bin", "median_output_small.bin", 10);
  case 5:
    return testRunningMedian("median_input_large.bin", "median_output_large.bin", 1000);
  case 6:
    return testHeapSort(0, 50);
  case 7:
    return testHeapSort(1, 50);
  case 8:
    return testHeapSort(2, 50);
  case 9:
    return testHeapSort(0, 500000);
  case 10:
    return testHeapSort(1, 500000);
  case 11:
    return testHeapSort(2, 500000);
  case 12:
    return testMergeSort(0, 50);
  case 13:
    return testMergeSort(1, 50);
  case 14:
    return testMergeSort(2, 50);
  case 15:
    return testMergeSort(0, 500000);
  case 16: 
    return testMergeSort(1, 500000);
  case 17:
    return testMergeSort(2, 500000);
  case 18:
    return testKthMin(0, 50);
  case 19:
    return testKthMin(1, 50);
  case 20:
    return testKthMin(2, 50);
  case 21:
    return testKthMin(0, 1000);
  case 22:
    return testKthMin(1, 1000);
  case 23:
    return testKthMin(2, 1000);
  default:
    return NULL;
  }
}

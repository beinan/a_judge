#pragma once

#include <vector>
#include <utility>
#include <string>

struct IVectorDoubleSort {
  IVectorDoubleSort() { }
  virtual ~IVectorDoubleSort() { }
  virtual void sort(std::vector<double>& vec) = 0;  
};

struct LinkedListNode {
  double key;
  LinkedListNode * next;
};

struct ILinkedListSort {
  ILinkedListSort() { }
  virtual ~ILinkedListSort() { }
  virtual LinkedListNode * sort(LinkedListNode * list) = 0;
};

struct IRunningMedian {
  IRunningMedian() { }
  virtual ~IRunningMedian() { }
  virtual std::vector<int> compute(std::vector<int> vec, int window_size) = 0;
};

struct IHeapSort {
  IHeapSort() {}
  virtual ~IHeapSort() {}
  virtual void sort(std::vector<int>& vector) = 0;
};

struct ISingleNode03 {
  ISingleNode03() {}
  virtual ~ISingleNode03() {}
  virtual int getValue() = 0;
  virtual void setValue(int value) = 0;
  virtual ISingleNode03 * getNext() = 0;
  virtual void setNext(ISingleNode03 * next) = 0;
};

struct ICircularList {
  ICircularList() {}
  virtual ~ICircularList() {}
  virtual void addHead(int number) = 0;
  virtual ISingleNode03 * getTail() = 0;
  virtual void setTail(ISingleNode03 * tail) = 0;
  virtual int size() = 0;
};

struct IDoubleNode03 {
  IDoubleNode03() {}
  virtual ~IDoubleNode03() {}
  virtual void setValue(int value) = 0;
  virtual int getValue() = 0;
  virtual IDoubleNode03 * getPrev() = 0;
  virtual IDoubleNode03 * getNext() = 0;
  virtual void setPrev(IDoubleNode03 * prev) = 0;
  virtual void setNext(IDoubleNode03 * next) = 0;
};

struct IDoubleList03 {
  IDoubleList03() {}
  virtual ~IDoubleList03() {}
  virtual IDoubleNode03 * getHead() = 0;
  virtual IDoubleNode03 * getTail() = 0;
  virtual void setHead(IDoubleNode03 * head) = 0;
  virtual void setTail(IDoubleNode03 * tail) = 0;
  virtual void addBack(int value) = 0;
  virtual int size() = 0;
};

struct IMergeSort {
  IMergeSort() {}
  virtual ~IMergeSort() {}
  virtual void mergeSort(ICircularList * input) = 0;
};

struct IKthMin {
  IKthMin() {}
  virtual ~IKthMin() {}
  virtual int findKthMin(IDoubleList03 * data, int k) = 0;
};

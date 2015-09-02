#pragma once

#include <cstdlib>

struct ISingleNode {
  ISingleNode() {}
  virtual ~ISingleNode() {}
  virtual void setValue(int value) = 0;
  virtual int getValue() = 0;
  virtual ISingleNode * getNext() = 0;
  virtual void setNext(ISingleNode * next) = 0;
};

struct ISingleList {
  ISingleList() {};
  virtual ~ISingleList() {};
  virtual ISingleNode * getHead() = 0;
  virtual void setHead(ISingleNode * head) = 0;
  virtual void addHead(int value) = 0;
  virtual void orderSort2() = 0;
  virtual void orderSort3() = 0;
  virtual void sequenceOrderSort() = 0;
  virtual void reverse() = 0;
};

struct IDoubleNode {
  IDoubleNode() {}
  virtual ~IDoubleNode() {}
  virtual void setValue(int value) = 0;
  virtual int getValue() = 0;
  virtual IDoubleNode * getPrev() = 0;
  virtual IDoubleNode * getNext() = 0;
  virtual void setPrev(IDoubleNode * prev) = 0;
  virtual void setNext(IDoubleNode * next) = 0;
};

struct IDoubleList {
  IDoubleList() {}
  virtual ~IDoubleList() {}
  virtual IDoubleNode * getHead() = 0;
  virtual IDoubleNode * getTail() = 0;
  virtual void setHead(IDoubleNode * head) = 0;
  virtual void setTail(IDoubleNode * tail) = 0;
  virtual void addSorted(int value) = 0;
  virtual void orderSort2() = 0;
  virtual void orderSort3() = 0;
  virtual void sequenceOrderSort() = 0;
  virtual void reverse() = 0;
};

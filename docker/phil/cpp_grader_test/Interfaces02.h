#pragma once

#define INTERFACES_KEYVALUE

#include <string>

struct IKeyValue {
  IKeyValue() {}
  virtual ~IKeyValue() {}
  virtual void setKey(int key) = 0;
  virtual void setValue(std::string value) = 0;
  virtual int getKey() = 0;
  virtual std::string getValue() = 0;
};

struct IVectorKeyValue {
  IVectorKeyValue() {}
  virtual ~IVectorKeyValue() {}
  virtual void push_back(IKeyValue * item) = 0;
  virtual void pop_back() = 0;
  virtual IKeyValue * get(int index) = 0;
  virtual void set(int index, IKeyValue * item) = 0;
  virtual size_t size() = 0;
};

struct IVectorString {
  IVectorString() {}
  virtual ~IVectorString() {}
  virtual void push_back(std::string item) = 0;
  virtual void pop_back() = 0;
  virtual std::string get(int index) = 0;
  virtual void set(int index, std::string item) = 0;
  virtual size_t size() = 0;
};

struct IPriorityQueue {
  IPriorityQueue() {}
  virtual ~IPriorityQueue() {}
  virtual void enqueue(IKeyValue * key_value) = 0;
  virtual IVectorKeyValue * returnSorted() = 0;
  virtual int lowestKey() = 0;
  virtual IVectorString * lowestValues() = 0;
  virtual void dequeue() = 0;
  virtual size_t size() = 0;
};

struct ITopN {
  ITopN() {}
  virtual ~ITopN() {}
  virtual IVectorKeyValue * returnTopN(IVectorKeyValue * vec_key_values, int n) = 0;
};


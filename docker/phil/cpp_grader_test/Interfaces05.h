#pragma once

#include <vector>
#include <cstdlib>
#include <string>

struct CompositeKey {
  int key1;
  float key2;
  int key3;

  void operator=(const CompositeKey& rhs);
  bool operator<(const CompositeKey& rhs) const;
  bool operator==(const CompositeKey& rhs) const;
  void operator=(CompositeKey& rhs);
  bool operator<(CompositeKey& rhs);
  bool operator==(CompositeKey& rhs);
};

struct IHashMap {
  IHashMap() { }
  virtual ~IHashMap() { }
  virtual void insert(CompositeKey key, int value) = 0;
  virtual void remove(CompositeKey key) = 0;
  virtual bool containsKey(CompositeKey key) = 0;
  virtual int getValue(CompositeKey key) = 0;
  virtual int kthMinValue(int k) = 0;
  virtual int size() = 0;
};

struct IBulkHashMap {
  IBulkHashMap() { }
  virtual ~IBulkHashMap() { } 
  virtual void insert(std::vector<std::pair<CompositeKey, int> >& data) = 0;
  virtual int getValue(CompositeKey key) = 0;
};

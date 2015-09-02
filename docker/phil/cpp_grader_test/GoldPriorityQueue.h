#pragma once

#include <vector>
#include <string>
#include <map>
#include <set>

class GoldPriorityQueue {
public:
  GoldPriorityQueue(std::vector<int> sorted_keys);
  void push_back(int key, std::string value);
  void iterate();
  bool hasNext();
  int nextKey();
  std::vector<std::string> nextValues();
  std::vector<std::string> getValues(int key);
  std::vector<std::pair<int, std::string> > returnSorted();
  int lowestKey();
  void dequeue();
  size_t size();
private:
  std::set<int> m_insertedKeys;
  std::vector<int> m_sortedKeys;
  std::map<int, std::vector<std::string> > m_values;
  std::map<int, std::vector<std::string> >::iterator m_iter;
  int m_iterKey;
};

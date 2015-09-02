#include "GoldPriorityQueue.h"
#include <algorithm>
#include <iostream>

GoldPriorityQueue::GoldPriorityQueue(std::vector<int> sorted_keys)
  : m_sortedKeys(sorted_keys)
{
}

void GoldPriorityQueue::push_back(int key, std::string value){
  m_insertedKeys.insert(key);
  std::vector<std::string> values = m_values[key];
  values.push_back(value);
  m_values[key] = values;
}
  
void GoldPriorityQueue::dequeue(){
  m_insertedKeys.erase(m_iterKey);
}

void GoldPriorityQueue::iterate(){
  m_iter = m_values.begin();
  m_iterKey = m_iter->first;
}
  
bool GoldPriorityQueue::hasNext(){
  if(m_iter == m_values.end()){
    return false;
  }
  m_iterKey = m_iter->first;
  ++m_iter;
  return true;
}
  
int GoldPriorityQueue::nextKey(){
  return m_iterKey;
}

std::vector<std::string> GoldPriorityQueue::nextValues(){
  int key = nextKey();
  return m_values[key];
}

std::vector<std::string> GoldPriorityQueue::getValues(int key){
  return m_values[key];
}

int GoldPriorityQueue::lowestKey(){
  return m_iterKey;
}

size_t GoldPriorityQueue::size(){
  return m_insertedKeys.size();
}

std::vector<std::pair<int, std::string> > 
GoldPriorityQueue::returnSorted(){

  std::vector<std::pair<int, std::string> > ret;
  std::set<int> visited;

  for(size_t i = 0; i < m_sortedKeys.size(); ++i){
    int key = m_sortedKeys[i];
    if(m_insertedKeys.find(key) == m_insertedKeys.end()){
      continue;
    }
    if(visited.find(key) != visited.end()){
      continue;
    }
    visited.insert(key);
    std::vector<std::string> values = m_values[key];
    for(size_t j = 0; j < values.size(); ++j){
      std::string value = values[j];
      ret.push_back(std::pair<int, std::string>(key, value));
    }
  }
  return ret;
}

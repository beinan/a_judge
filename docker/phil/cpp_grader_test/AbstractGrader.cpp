#include <sstream>
#include "AbstractGrader.h"
#include "ObjectFactory.h"
#include "Random.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <fstream>

#ifdef linux
#include <dlfcn.h>
#endif

AbstractGrader::AbstractGrader()
  : m_dllHandle(NULL), m_letters("abcdefghijklmnopqrstuvwxyz")
{
}

AbstractGrader::~AbstractGrader()
{
}

void AbstractGrader::print(IVectorString * values){
  std::cout << "[" << std::endl;
  for(size_t i = 0; i < values->size(); ++i){
    std::cout << "  {" << values->get(i) << "}" << std::endl;
  }
  std::cout << "]" << std::endl;
}

void AbstractGrader::print(std::vector<std::string>& values){
  std::cout << "[" << std::endl;
  for(size_t i = 0; i < values.size(); ++i){
    std::cout << "  {" << values[i] << "}" << std::endl;
  }
  std::cout << "]" << std::endl;
}

bool AbstractGrader::valuesEqual(IVectorString * user_values, 
  std::vector<std::string>& gold_values)
{
  //print(user_values);
  //print(gold_values);
  if(user_values->size() != gold_values.size()){
    return false;
  }

  std::set<std::string> user_set;
  for(int i = 0; i < user_values->size(); ++i){
    user_set.insert(user_values->get(i));
  }

  for(int i = 0; i < gold_values.size(); ++i){
    std::string gold_value = gold_values[i];
    if(user_set.find(gold_value) == user_set.end()){
      return false;
    }
  }
  return true;
}

void AbstractGrader::loadBinarySequence(std::string filename, std::vector<std::pair<int, int> >& seq){
  std::ifstream fin(filename.c_str(), std::ios::binary);
  if(fin.good() == false){
    return;
  }
  size_t len;
  fin.read((char *) &len, sizeof(size_t));
  for(size_t i = 0; i < len; ++i){
    int first;
    int second;
    fin.read((char *) &first, sizeof(int));
    fin.read((char *) &second, sizeof(int));
    seq.push_back(std::pair<int, int>(first, second));
  }
  fin.close();
}

void AbstractGrader::loadBinarySequence(std::string filename, std::vector<double>& seq){
  std::ifstream fin(filename.c_str(), std::ios::binary);
  if(fin.good() == false){
    return;
  }
  size_t len;
  fin.read((char *) &len, sizeof(size_t));
  for(size_t i = 0; i < len; ++i){
    double value;
    fin.read((char *) &value, sizeof(double));
    seq.push_back(value);
  }
  fin.close();
}

void AbstractGrader::loadBinarySequence(std::string filename, std::vector<int>& seq){
  std::ifstream fin(filename.c_str(), std::ios::binary);
  if(fin.good() == false){
    return;
  }
  size_t len;
  fin.read((char *) &len, sizeof(size_t));
  for(size_t i = 0; i < len; ++i){
    int value;
    fin.read((char *) &value, sizeof(int));
    seq.push_back(value);
  }
  fin.close();
}

void AbstractGrader::print(IVectorKeyValue * vector){
  std::cout << "[" << std::endl;
  for(size_t i = 0; i < vector->size(); ++i){
    std::cout << "  {" << vector->get(i)->getKey() << "," << vector->get(i)->getValue() << "}" << std::endl;
  }
  std::cout << "]" << std::endl;
}

void AbstractGrader::print(std::vector<std::pair<int, std::string> >& vector){
  std::cout << "[" << std::endl;
  for(size_t i = 0; i < vector.size(); ++i){
    std::cout << "  {" << vector[i].first << "," << vector[i].second << "}" << std::endl;
  }
  std::cout << "]" << std::endl;
}

bool AbstractGrader::sortedEqual(IVectorKeyValue * user_sorted, 
  std::vector<std::pair<int, std::string> > gold_vector)
{
  if(user_sorted == NULL){
    return false;
  }

  //print(user_sorted);
  //print(gold_vector);
  if(user_sorted->size() != gold_vector.size()){
    return false;
  }
  for(size_t i = 0; i < gold_vector.size(); ++i){
    std::pair<int, std::string> gold_item = gold_vector[i];
    IKeyValue * user_item = user_sorted->get(i);

    if(gold_item.first != user_item->getKey()){
      return false;
    }

    if(gold_item.second != user_item->getValue()){
      return false;
    }
  }
  return true;
}

bool AbstractGrader::vectorEqual(std::vector<double>& lhs, std::vector<double>& rhs){
  if(lhs.size() != rhs.size()){
    return false;
  }
  for(size_t i = 0; i < lhs.size(); ++i){
    double lhs_value = lhs[i];
    double rhs_value = rhs[i];
    if(lhs_value != rhs_value){
      return false;
    }
  }
  return true;
}

bool AbstractGrader::vectorEqual(std::vector<int>& lhs, std::vector<int>& rhs){
  if(lhs.size() != rhs.size()){
    return false;
  }
  for(size_t i = 0; i < lhs.size(); ++i){
    int lhs_value = lhs[i];
    int rhs_value = rhs[i];
    if(lhs_value != rhs_value){
      return false;
    }
  }
  return true;
}

bool AbstractGrader::VectorsEqual(IVectorKeyValue * user_vec,
                  std::vector<std::pair<int, std::string> > gold_vec){
  if(user_vec->size() != gold_vec.size())
    return false;

  for(int i = 0; i < gold_vec.size(); ++i){
    if(user_vec->get(i)->getKey() != gold_vec[i].first ||
        user_vec->get(i)->getValue() != gold_vec[i].second)
      return false;
  }

  return true;
}

std::string AbstractGrader::randomValue()
{
  std::string ret = "";
  for(int i = 0; i < 6; ++i){
    int index = m_rand.nextInt(m_letters.size());
    ret += m_letters[index];
  }
  return ret;
}

void AbstractGrader::setDllHandle(void * dll_handle){
  m_dllHandle = dll_handle;
}

std::string AbstractGrader::toString(int value)
{
  std::ostringstream oss;
  oss << value;
  return oss.str();
}

void AbstractGrader::viewVector(std::vector<int>& input, 
  std::vector<int>& output, int len, int order)
{
  std::vector<int> indices;
  for(size_t i = 0; i < input.size(); ++i){
    indices.push_back(i);
  }

  if(order == 1){
    std::reverse(indices.begin(), indices.end());
  } else if(order == 2){
    std::random_shuffle(indices.begin(), indices.end());
  }

  for(int i = 0; i < len; ++i){
    int index = indices[i];
    output.push_back(input[index]);
  }
}

void AbstractGrader::createVector(std::vector<int>& input, std::vector<int>& sorted, 
  int order, int len, bool duplicates)
{
  Random random;
  std::vector<int> counts;
  if(duplicates){
    for(int i = 0; i < len / 2; ++i){
      counts.push_back(1);
    }
    for(int i = 0; i < len / 4; ++i){
      counts.push_back(2);
    }
    for(int i = 0; i < len / 8; ++i){
      counts.push_back(3);
    }
    for(int i = 0; i < len / 16; ++i){
      counts.push_back(4);
    }
    for(int i = 0; i < len / 32; ++i){
      counts.push_back(5);
    }
    std::random_shuffle(counts.begin(), counts.end());  
    for(int i = 0; i < len; ++i){
      int count = 1;
      if(i < counts.size()){
        count = counts[i];
      }
      for(int j = 0; j < count && sorted.size() < len; ++j){
        sorted.push_back(i);
      }
    } 
  } else {
    for(int i = 0; i < len; ++i){
      sorted.push_back(i);
    }
  }


  if(order == 0){
    input = sorted;
  } else if(order == 1){
    input = sorted;
    std::reverse(input.begin(), input.end());
  } else {
    input = sorted;
    std::random_shuffle(input.begin(), input.end());
  }
}

TestCase * AbstractGrader::nullObject(std::string iface)
{
  TestCase * ret = new TestCase();
  ret->passed = false;
  ret->error_message = std::string("null object returned for interface: ")+iface;
  ret->time = 0;
  return ret;
}

TestCase * AbstractGrader::failed(std::string error_message)
{
  TestCase * ret = new TestCase();
  ret->passed = false;
  ret->error_message = error_message;
  ret->time = 0;
  return ret;
}

TestCase * AbstractGrader::passed(long time)
{
  TestCase * ret = new TestCase();
  ret->passed = true;
  ret->error_message = "no error";
  ret->time = time;
  return ret;
}

void * AbstractGrader::createObject(std::string name){
#ifdef GRADE_SERVER
  void *(*fptr)() = (void *(*)()) dlsym(m_dllHandle, "createObjectFactory");
#else
  void *(*fptr)() = (void *(*)()) &createObjectFactory;
#endif
    
  void * ret = (*fptr)();
  ObjectFactory * fact = (ObjectFactory *) ret;
  return fact->create(name);
}

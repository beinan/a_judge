#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "Interfaces02.h"
#include "GoldPriorityQueue.h"
#include "TestCase.h"
#include "Stopwatch.h"
#include "Grader02.h"


const TestCaseInfo2 Grader02::kTestCases[kTestCasesSize] = {
    { 7, "workload1 small ascending", "workload1_small_ascending.bin", &Grader02::testWorkload1 },
    { 7, "workload1 small descending", "workload1_small_descending.bin", &Grader02::testWorkload1},
    { 7, "workload1 small random", "workload1_small_random.bin", &Grader02::testWorkload1 },
    { 7, "workload1 large ascending", "workload1_large_ascending.bin", &Grader02::testWorkload1 },
    { 7, "workload1 large descending", "workload1_large_descending.bin", &Grader02::testWorkload1 },
    { 7, "workload1 large random", "workload1_large_random.bin", &Grader02::testWorkload1 },

    { 7, "workload2 small ascending", "workload2_small_ascending.bin", &Grader02::testWorkload2 },
    { 7, "workload2 small descending", "workload2_small_descending.bin", &Grader02::testWorkload2},
    { 7, "workload2 small random", "workload2_small_random.bin", &Grader02::testWorkload2 },
    { 7, "workload2 large ascending", "workload2_large_ascending.bin", &Grader02::testWorkload2 },
    { 7, "workload2 large descending", "workload2_large_descending.bin", &Grader02::testWorkload2 },
    { 7, "workload2 large random", "workload2_large_random.bin", &Grader02::testWorkload2 },

    { 8, "workload3 small", "workload3_small.bin", &Grader02::testWorkload3 },
    { 8, "workload3 large", "workload3_large.bin", &Grader02::testWorkload3 }
};

void Grader02::loadVector(std::ifstream& fin, std::vector<int>& vec){
  long long len;
  fin.read((char *)&len, sizeof(long long));

  for (size_t i = 0; i < len; ++i){
    int val;
    fin.read((char *)&val, sizeof(int));
    vec.push_back(val);
  }
}

bool Grader02::loadVectors(const std::string& file_name,
                           std::vector<int>& input,
                           std::vector<int>& sorted){
  std::ifstream fin(file_name.c_str(), std::ios::binary);
  if (!fin.good()){
    return false;
  }

  loadVector(fin, input);
  loadVector(fin, sorted);
  fin.close();

  return true;
}

TestCase * Grader02::testWorkload1(int test_case){
  std::vector<int> input;
  std::vector<int> sorted;

  bool file_is_open = loadVectors(kTestCases[test_case].test_file, input, sorted);
  if(!file_is_open){
    return failed("Cannot open file " + kTestCases[test_case].test_file);
  }
  size_t len = input.size();

  Stopwatch watch;
  watch.start();

  IPriorityQueue * queue = (IPriorityQueue *) createObject("IPriorityQueue1");
  if(queue == NULL){
    return nullObject("IPriorityQueue1");
  }

  watch.pause();
  GoldPriorityQueue gold_queue(sorted);
  for(size_t i = 0; i < input.size(); ++i){
    int key = input[i];
    std::string value = randomValue();
    gold_queue.push_back(key, value);

    watch.unpause();
    IKeyValue * key_value = (IKeyValue *) createObject("IKeyValue1");
    if(key_value == NULL){
      return nullObject("IKeyValue1");
    }

    key_value->setKey(key);
    key_value->setValue(value);

    queue->enqueue(key_value);

    size_t size = queue->size();
    if(size != gold_queue.size()){
      return failed("after enqueue, size is incorrect");
    }

    int user_key = queue->lowestKey();
    IVectorString * user_values = queue->lowestValues();
    gold_queue.iterate();
    int gold_key = gold_queue.lowestKey();
    std::vector<std::string> values = gold_queue.getValues(gold_key);
    watch.pause();        

    if(gold_key != user_key){
      return failed("after enqueue, lowest key is incorrect");
    }

    if(!valuesEqual(user_values, values)){
      return failed("after enqueue, values incorrect");
    }

    bool check_sort = true;
    if(len != 10 && i % 100 != 0){
      check_sort = false;
    }

    if(check_sort){
      watch.unpause();
      IVectorKeyValue * user_sorted = queue->returnSorted();
      watch.pause();
      if(!sortedEqual(user_sorted, gold_queue.returnSorted())){
        return failed("after enqueue, sorted is not equal");
      } 
    }
  }

  gold_queue.iterate();
  int count = 0;
  while(gold_queue.hasNext()){
    watch.unpause();
    int user_key = queue->lowestKey();
    IVectorString * user_values = queue->lowestValues();
    watch.pause();    

    int gold_key = gold_queue.lowestKey();
    std::vector<std::string> values = gold_queue.getValues(gold_key);

    if(gold_key != user_key){
      return failed("during dequeue, lowest key is incorrect");
    }

    if(!valuesEqual(user_values, values)){
      return failed("during dequeue, values incorrect");
    }

    watch.unpause();
    size_t size = queue->size();
    watch.pause();    
    if(size != gold_queue.size()){
      return failed("during dequeue, size is incorrect");
    }

    bool check_sort = true;
    if(len != 10 && count % 100 != 0){
      check_sort = false;
    }

    if(check_sort){
      IVectorKeyValue * user_sorted = queue->returnSorted();
      std::vector<std::pair<int, std::string> > gold_sorted = gold_queue.returnSorted();
      if(!sortedEqual(user_sorted, gold_sorted)){
        return failed("during dequeue, sorted is not equal");
      } 
    }
  
    watch.unpause();
    queue->dequeue();
    watch.pause();    
    gold_queue.dequeue();
    ++count;
  }
  
  delete queue;
 
  return passed(watch.getTime());
}

TestCase * Grader02::testWorkload2(int test_case){
  std::vector<int> input;
  std::vector<int> sorted;

  bool file_is_open = loadVectors(kTestCases[test_case].test_file, input, sorted);
  if(!file_is_open){
    return failed("Cannot open file " + kTestCases[test_case].test_file);
  }

  Stopwatch watch;
  watch.start();

  IPriorityQueue * queue = (IPriorityQueue *) createObject("IPriorityQueue2");
  if(queue == NULL){
    return nullObject("IPriorityQueue2");
  }

  watch.pause();
  GoldPriorityQueue gold_queue(sorted);
  for(size_t i = 0; i < input.size(); ++i){
    int key = input[i];
    std::string value = randomValue();
    gold_queue.push_back(key, value);

    watch.unpause();
    IKeyValue * key_value = (IKeyValue *) createObject("IKeyValue2");
    if(key_value == NULL){
      return nullObject("IKeyValue2");
    }

    key_value->setKey(key);
    key_value->setValue(value);

    queue->enqueue(key_value);

    size_t size = queue->size();
    if(size != gold_queue.size()){
      return failed("after enqueue, size is incorrect");
    }

    int user_key = queue->lowestKey();
    IVectorString * user_values = queue->lowestValues();
    gold_queue.iterate();
    int gold_key = gold_queue.lowestKey();
    std::vector<std::string> values = gold_queue.getValues(gold_key);
    watch.pause();        

    if(gold_key != user_key){
      return failed("after enqueue, lowest key is incorrect");
    }

    if(!valuesEqual(user_values, values)){
      return failed("after enqueue, values incorrect");
    }
  }

  gold_queue.iterate();
  int count = 0;
  while(gold_queue.hasNext()){
    watch.unpause();
    int user_key = queue->lowestKey();
    IVectorString * user_values = queue->lowestValues();
    watch.pause();    

    int gold_key = gold_queue.lowestKey();
    std::vector<std::string> values = gold_queue.getValues(gold_key);

    if(gold_key != user_key){
      return failed("during dequeue, lowest key is incorrect");
    }

    if(!valuesEqual(user_values, values)){
      return failed("during dequeue, values incorrect");
    }

    watch.unpause();
    size_t size = queue->size();
    watch.pause();    
    if(size != gold_queue.size()){
      return failed("during dequeue, size is incorrect");
    }

    watch.unpause();
    queue->dequeue();
    watch.pause();    
    gold_queue.dequeue();
    ++count;
  }
  
  delete queue;
 
  return passed(watch.getTime());
}

TestCase * Grader02::testWorkload3(int test_case) {
  std::vector<int> input;
  std::vector<int> sorted;

  bool file_is_open = loadVectors(kTestCases[test_case].test_file, input, sorted);
  if(!file_is_open){
    return failed("Cannot open file " + kTestCases[test_case].test_file);
  }

  std::vector<std::pair<int, std::string> > gold_input;
  for(size_t i = 0; i < input.size(); ++i){
    int key = input[i];
    std::string value = randomValue();
    gold_input.push_back(std::pair<int, std::string>(key, value));
  }

  Stopwatch watch;
  watch.start();

  IVectorKeyValue * vec_key_values = (IVectorKeyValue *) createObject("IVectorKeyValue3");
  if(vec_key_values == NULL){
    return nullObject("IVectorKeyValue3");
  }

  for(size_t i = 0; i < input.size(); ++i){
    IKeyValue * key_value = (IKeyValue *) createObject("IKeyValue3");
    if(key_value == NULL){
      return nullObject("IKeyValue3");
    }

    key_value->setKey(gold_input[i].first);
    key_value->setValue(gold_input[i].second);
    vec_key_values->push_back(key_value);
  }

  watch.pause();
  if(vec_key_values->size() != gold_input.size()){
    return failed("VectorKeyValue's size is not correct");
  }
  if(!VectorsEqual(vec_key_values, gold_input)){
    return failed("KeyValues incorrect");
  }

  watch.unpause();
  ITopN *topN = (ITopN *) createObject("ITopN");
  if(topN == NULL){
    return nullObject("ITopN");
  }

  int n = sorted.size();
  IVectorKeyValue * result = topN->returnTopN(vec_key_values, n);

  watch.pause();

  if(result->size() != sorted.size()){
    return failed("topN result size incorrect");
  }
  for(int i = 0; i < sorted.size(); ++i) {
    if (result->get(i)->getKey() != sorted[i])
      return failed("topN result values incorrect");
  }
  
  delete topN;

  return passed(watch.getTime());
}

int Grader02::size(){
  return kTestCasesSize;
}

std::string Grader02::getDescription(int test_case)
{
  if (test_case >= size())
    return "";

  return kTestCases[test_case].description;
}

int Grader02::getPoints(int test_case)
{
  if (test_case >= size())
    return 0;

  return kTestCases[test_case].point;
}

Date Grader02::getDueDate()
{
  return Date(1, 1, 2011);
}

TestCase * Grader02::grade(int index){
  if (index >= size())
    return NULL;

  return (this->*kTestCases[index].test_func)(index);
}

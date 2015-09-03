#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <set>
#include "Commands05.h"
#include "Interfaces05.h"
#include "TestCase.h"
#include "Stopwatch.h"
#include <cmath>
#include <fstream>
#include "Grader05.h"
#include "MemUsage.h"

TestCase * Grader05::testHashMap(std::string filename, std::string iface)
{
  std::vector<HashMapCmd> commands;
  Commands05 cmds05;
  cmds05.loadHashMapCommmands(filename, commands);

  if(commands.size() == 0){
    return failed("cannot load input file");
  }

  MemUsage mem_usage;
  long long mem_sum = 0;
  long long mem_count = 0;

  Stopwatch watch;
  watch.start();
  IHashMap * hashmap = (IHashMap *) createObject(iface);
  if(hashmap == NULL){
    return nullObject(iface);
  }
  for(size_t i = 0; i < commands.size(); ++i){
    HashMapCmd cmd = commands[i];
    if(cmd.action == HASHMAP_CMD_INSERT){
      //std::cout << "insert: [" << cmd.input.key1 << "," << cmd.input.key2 << "," << cmd.input.key3 << "]" << std::endl;
      hashmap->insert(cmd.input, cmd.output);
    } else if(cmd.action == HASHMAP_CMD_REMOVE){
      //std::cout << "remove: [" << cmd.input.key1 << "," << cmd.input.key2 << "," << cmd.input.key3 << "]" << std::endl;
      hashmap->remove(cmd.input);
    } else if(cmd.action == HASHMAP_CMD_CONTAINS){
      //std::cout << "contains: [" << cmd.input.key1 << "," << cmd.input.key2 << "," << cmd.input.key3 << "]" << std::endl;
      bool contains = hashmap->containsKey(cmd.input);
      if(contains){
        if(cmd.output == COMMANDS05_FALSE){
          return failed("error in containsKey #1");
        }
      } else {
        if(cmd.output == COMMANDS05_TRUE){
          return failed("error in containsKey #2");
        }
      }
    } else if(cmd.action == HASHMAP_CMD_QUERY){
      //std::cout << "query: [" << cmd.input.key1 << "," << cmd.input.key2 << "," << cmd.input.key3 << "]" << std::endl;
      int value = hashmap->getValue(cmd.input);
      if(value != cmd.output){
        return failed("error in query");
      }
    } else if(cmd.action == HASHMAP_CMD_KTH){
      //std::cout << "kth: " << cmd.input_kth << std::endl;
      int k = cmd.input_kth;
      if(k >= hashmap->size()){
        return failed("error in kth (size)");
      }      
      int value = hashmap->kthMinValue(k);
      if(value != cmd.output){
        return failed("error in kth (kthMinValue)");
      }    
    } else {
      return failed("internal error in test case");
    }
    if(i % 100 == 0){
      mem_sum += mem_usage.getUsage();
      mem_count++;
    }
  }

  watch.stop();

  long long usage = mem_sum / mem_count;
  std::cout << "mem_usage: " << usage << std::endl;
  std::cout << "time: " << watch.getTime() << std::endl;
  return passed(watch.getTime() + usage);
}

TestCase * Grader05::testHashMapBulk(std::string data_filename, std::string cmds_filename)
{  
  std::vector<HashMapCmd> commands;
  std::vector<std::pair<CompositeKey, int> > data;  

  Commands05 cmds05;
  cmds05.loadHashMapCommmands(cmds_filename, commands);
  cmds05.loadHashMapData(data_filename, data);

  if(commands.size() == 0){
    return failed("cannot load input file #1");
  }

  MemUsage mem_usage;
  long long mem_sum = 0;
  long long mem_count = 0;

  if(data.size() == 0){
    return failed("cannot load input file #2");
  }

  IBulkHashMap * hashmap = (IBulkHashMap *) createObject("IBulkHashMap");
  if(hashmap == NULL){
    return nullObject("IBulkHashMap");
  }

  hashmap->insert(data);

  Stopwatch watch;
  watch.start();
  for(size_t i = 0; i < commands.size(); ++i){
    HashMapCmd cmd = commands[i];
    if(cmd.action == HASHMAP_CMD_QUERY){
      //std::cout << "query: [" << cmd.input.key1 << "," << cmd.input.key2 << "," << cmd.input.key3 << "]" << std::endl;
      int value = hashmap->getValue(cmd.input);
      if(value != cmd.output){
        return failed("error in query");
      }
    } else {
      return failed("internal error in test case");
    }
    if(i % 100 == 0){    
      mem_sum += mem_usage.getUsage();
      mem_count++;
    }
  }

  watch.stop();

  long long usage = mem_sum / mem_count;
  std::cout << "mem_usage: " << usage << std::endl;
  std::cout << "time: " << watch.getTime() << std::endl;
  return passed(watch.getTime() + usage);
}

int Grader05::size(){
  return 10;
}

std::string Grader05::getDescription(int test_case)
{
  switch(test_case){
  case 0: return "HashMap Small Insert Random";
  case 1: return "HashMap Large Insert Random";
  case 2: return "HashMap Small Insert/Remove Random";
  case 3: return "HashMap Large Insert/Remove Random";
  case 4: return "HashMap Small Insert/Kth Random";
  case 5: return "HashMap Large Insert/Kth Random";
  case 6: return "HashMap Small Insert/Remove/Kth Random";
  case 7: return "HashMap Large Insert/Remove/Kth Random";
  case 8: return "BulkHashMap Insert Small Random";
  case 9: return "BulkHashMap Insert Large Random";
  }
  return "";
}

int Grader05::getPoints(int test_case)
{
  switch(test_case){
  case 0: return 10;
  case 1: return 10;
  case 2: return 10;
  case 3: return 10;
  case 4: return 10;
  case 5: return 10;
  case 6: return 10;
  case 7: return 10;
  case 8: return 10;
  case 9: return 10;
  }
  return 0;
}

Date Grader05::getDueDate()
{
  return Date(11, 28, 2013);
}
  
TestCase * Grader05::grade(int index){
  switch(index){
  case 0:
    return testHashMap("hashmap_1.bin", "IHashMap1");
  case 1:
    return testHashMap("hashmap_2.bin", "IHashMap1");
  case 2:
    return testHashMap("hashmap_3.bin", "IHashMap2");
  case 3:
    return testHashMap("hashmap_4.bin", "IHashMap2");
  case 4:
    return testHashMap("hashmap_5.bin", "IHashMap3");
  case 5:
    return testHashMap("hashmap_6.bin", "IHashMap3");
  case 6:
    return testHashMap("hashmap_7.bin", "IHashMap4");
  case 7:
    return testHashMap("hashmap_8.bin", "IHashMap4");
  case 8:
    return testHashMapBulk("hashmap_9_data.bin", "hashmap_9.bin");
  case 9:
    return testHashMapBulk("hashmap_10_data.bin", "hashmap_10.bin");
  default:
    return NULL;
  }
}

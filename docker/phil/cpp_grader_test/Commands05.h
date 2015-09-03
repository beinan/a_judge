#pragma once

#include <vector>
#include <string>
#include <set>
#include <map>
#include "Interfaces05.h"

#define HASHMAP_CMD_INSERT   0
#define HASHMAP_CMD_REMOVE   1
#define HASHMAP_CMD_CONTAINS 2
#define HASHMAP_CMD_QUERY    3
#define HASHMAP_CMD_KTH      4

#define COMMANDS05_FALSE     0
#define COMMANDS05_TRUE      1

struct HashMapCmd {
  int action;
  CompositeKey input;
  int input_kth;
  int output;
};

class Commands05 {
public:
  void loadHashMapCommmands(std::string filename, std::vector<HashMapCmd>& cmds);
  void saveHashMapCommmands(std::string filename, std::vector<HashMapCmd>& cmds);
  void loadHashMapData(std::string filename, std::vector<std::pair<CompositeKey, int> >& data);
  void saveHashMapData(std::string filename, std::vector<std::pair<CompositeKey, int> >& data);

  std::string readString(std::ifstream& fin);
  void writeString(std::ofstream& fout, std::string str);
};

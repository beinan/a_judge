#pragma once

#include <vector>
#include <string>
#include <set>

#define AVL_CMD_INSERT 0
#define AVL_CMD_REMOVE 1
#define AVL_CMD_CHECK_SORT 2
#define AVL_CMD_KTH 3

#define BTREE_CMD_INSERT 0
#define BTREE_CMD_REMOVE 1
#define BTREE_CMD_CHECK_SORT 2
#define BTREE_CMD_KTH 3

struct AVLTreeCmd {
  int action;
  int input;
  int output;
};

struct BTreeCmd {
  int action;
  int input;
  int output;
};

class Commands04 {
public:
  void loadAVLTreeCommands(std::string cmds_filename, std::vector<AVLTreeCmd>& cmds);
  void saveAVLTreeCommands(std::string cmds_filename, std::vector<AVLTreeCmd>& cmds);

  void loadBTreeCommands(std::string cmds_filename, std::vector<BTreeCmd>& cmds);
  void saveBTreeCommands(std::string cmds_filename, std::vector<BTreeCmd>& cmds);
};

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

struct RTreePoint {
  int x;
  int y;

  bool operator<(const RTreePoint& rhs) const {
    if(x < rhs.x){
      return true;
    } else if(x > rhs.x){
      return false;
    } else if(y < rhs.y){
      return true;
    } else {
      return false;
    }
  }
};

struct RTreeCmd {
  int top_left_x;
  int top_left_y;
  int bottom_right_x;
  int bottom_right_y;
  std::set<RTreePoint> found;
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

  void loadRTreePoints(std::string filename, std::vector<RTreePoint>& points);
  void saveRTreePoints(std::string filename, std::vector<RTreePoint>& points);

  void loadRTreeCommands(std::string filename, std::vector<RTreeCmd>& cmds);
  void saveRTreeCommands(std::string filename, std::vector<RTreeCmd>& cmds);

  void loadBTreeCommands(std::string cmds_filename, std::vector<BTreeCmd>& cmds);
  void saveBTreeCommands(std::string cmds_filename, std::vector<BTreeCmd>& cmds);
};

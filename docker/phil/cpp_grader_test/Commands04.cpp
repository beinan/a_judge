#include "Commands04.h"
#include <fstream>

void Commands04::saveAVLTreeCommands(std::string cmds_filename, std::vector<AVLTreeCmd>& cmds)
{
  std::ofstream fout(cmds_filename.c_str(), std::ios::binary);
  if(fout.good() == false){
    return;
  }

  long long len = cmds.size();
  fout.write((char *) &len, sizeof(long long));
  for(long long i = 0; i < len; ++i){
    AVLTreeCmd curr = cmds[i];
    fout.write((char *) &(curr.action), sizeof(int));
    fout.write((char *) &(curr.input), sizeof(int));
    fout.write((char *) &(curr.output), sizeof(int));
  }
  fout.flush();
  fout.close();
}

void Commands04::loadAVLTreeCommands(std::string cmds_filename, std::vector<AVLTreeCmd>& cmds)
{
  std::ifstream fin(cmds_filename.c_str(), std::ios::binary);
  if(fin.good() == false){
    return;
  }

  long long len;
  fin.read((char *) &len, sizeof(long long));
  for(long long i = 0; i < len; ++i){
    AVLTreeCmd curr;
    fin.read((char *) &(curr.action), sizeof(int));
    fin.read((char *) &(curr.input), sizeof(int));
    fin.read((char *) &(curr.output), sizeof(int));
    cmds.push_back(curr);
  }
}

void Commands04::saveRTreePoints(std::string filename, std::vector<RTreePoint>& points)
{
  std::ofstream fout(filename.c_str(), std::ios::binary);
  if(fout.good() == false){
    return;
  }
  long long len = points.size();
  fout.write((char *) &len, sizeof(long long));
  for(int i = 0; i < len; ++i){
    RTreePoint curr = points[i];
    fout.write((char *) &(curr.x), sizeof(int));
    fout.write((char *) &(curr.y), sizeof(int));
  }
  fout.close();
}

void Commands04::loadRTreePoints(std::string filename, std::vector<RTreePoint>& points)
{
  std::ifstream fin(filename.c_str(), std::ios::binary);
  if(fin.good() == false){
    return;
  }

  long long len;
  fin.read((char *) &len, sizeof(long long));
  for(int i = 0; i < len; ++i){
    RTreePoint curr;
    fin.read((char *) &(curr.x), sizeof(int));
    fin.read((char *) &(curr.y), sizeof(int));
    points.push_back(curr);
  }
  fin.close();
}

void Commands04::saveRTreeCommands(std::string filename, std::vector<RTreeCmd>& cmds)
{
  std::ofstream fout(filename.c_str(), std::ios::binary);
  if(fout.good() == false){
    return;
  }
  long long len = cmds.size();
  fout.write((char *) &len, sizeof(long long));
  for(int i = 0; i < len; ++i){
    RTreeCmd curr = cmds[i];
    fout.write((char *) &(curr.top_left_x), sizeof(int));
    fout.write((char *) &(curr.top_left_y), sizeof(int));
    fout.write((char *) &(curr.bottom_right_x), sizeof(int));
    fout.write((char *) &(curr.bottom_right_y), sizeof(int));
    long long len2 = curr.found.size();
    fout.write((char *) &len2, sizeof(long long));
    std::set<RTreePoint>::iterator iter = curr.found.begin();
    while(iter != curr.found.end()){
      RTreePoint match_point = *iter;
      fout.write((char *) &(match_point.x), sizeof(int));
      fout.write((char *) &(match_point.y), sizeof(int));
      ++iter;
    }
  }
  fout.close();
}

void Commands04::loadRTreeCommands(std::string filename, std::vector<RTreeCmd>& cmds)
{
  std::ifstream fin(filename.c_str(), std::ios::binary);
  if(fin.good() == false){
    return;
  }

  long long len;
  fin.read((char *) &len, sizeof(long long));
  for(int i = 0; i < len; ++i){
    RTreeCmd curr;
    fin.read((char *) &(curr.top_left_x), sizeof(int));
    fin.read((char *) &(curr.top_left_y), sizeof(int));
    fin.read((char *) &(curr.bottom_right_x), sizeof(int));
    fin.read((char *) &(curr.bottom_right_y), sizeof(int));
    long long len2;
    fin.read((char *) &len2, sizeof(long long));
    for(int j = 0; j < len2; ++j){
      RTreePoint found_point;
      fin.read((char *) &(found_point.x), sizeof(int));
      fin.read((char *) &(found_point.y), sizeof(int));
      curr.found.insert(found_point);
    }
    cmds.push_back(curr);
  }
  fin.close();
}

void Commands04::saveBTreeCommands(std::string cmds_filename, std::vector<BTreeCmd>& cmds)
{
  std::ofstream fout(cmds_filename.c_str(), std::ios::binary);
  if(fout.good() == false){
    return;
  }

  long long len = cmds.size();
  fout.write((char *) &len, sizeof(long long));
  for(long long i = 0; i < len; ++i){
    BTreeCmd curr = cmds[i];
    fout.write((char *) &(curr.action), sizeof(int));
    fout.write((char *) &(curr.input), sizeof(int));
    fout.write((char *) &(curr.output), sizeof(int));
  }
  fout.flush();
  fout.close();
}

void Commands04::loadBTreeCommands(std::string cmds_filename, std::vector<BTreeCmd>& cmds)
{
  std::ifstream fin(cmds_filename.c_str(), std::ios::binary);
  if(fin.good() == false){
    return;
  }

  long long len;
  fin.read((char *) &len, sizeof(long long));
  for(long long i = 0; i < len; ++i){
    BTreeCmd curr;
    fin.read((char *) &(curr.action), sizeof(int));
    fin.read((char *) &(curr.input), sizeof(int));
    fin.read((char *) &(curr.output), sizeof(int));
    cmds.push_back(curr);
  }
}


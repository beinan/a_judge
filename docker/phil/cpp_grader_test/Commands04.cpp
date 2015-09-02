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


#include "Commands05.h"
#include <fstream>

std::string Commands05::readString(std::ifstream& fin)
{
  int size;
  fin.read((char *) &size, sizeof(int));
  char * ch = new char[size+1];
  fin.read((char *) ch, sizeof(char)*size);
  ch[size] = 0;
  std::string ret(ch);
  delete [] ch;
  return ret;
}

void Commands05::writeString(std::ofstream& fout, std::string str)
{
  int size = str.size();
  fout.write((char *) &size, sizeof(int));
  char * ch = new char[size];
  fout.write((char *) str.c_str(), sizeof(char)*size);
}

void Commands05::loadHashMapCommmands(std::string cmds_filename, std::vector<HashMapCmd>& cmds)
{
  std::ifstream fin(cmds_filename.c_str(), std::ios::binary);
  if(fin.good() == false){
    return;
  }

  long long len;
  fin.read((char *) &len, sizeof(long long));
  for(long long i = 0; i < len; ++i){
    HashMapCmd curr;
    fin.read((char *) &(curr.action), sizeof(int));
    fin.read((char *) &(curr.input.key1), sizeof(int));
    fin.read((char *) &(curr.input.key2), sizeof(float));
    fin.read((char *) &(curr.input.key3), sizeof(int));
    fin.read((char *) &(curr.input_kth), sizeof(int));
    fin.read((char *) &(curr.output), sizeof(int));
    cmds.push_back(curr);
  }
}

void Commands05::saveHashMapCommmands(std::string cmds_filename, std::vector<HashMapCmd>& cmds)
{
  std::ofstream fout(cmds_filename.c_str(), std::ios::binary);
  if(fout.good() == false){
    return;
  }

  long long len = cmds.size();
  fout.write((char *) &len, sizeof(long long));
  for(long long i = 0; i < len; ++i){
    HashMapCmd curr = cmds[i];
    fout.write((char *) &(curr.action), sizeof(int));
    fout.write((char *) &(curr.input.key1), sizeof(int));
    fout.write((char *) &(curr.input.key2), sizeof(float));
    fout.write((char *) &(curr.input.key3), sizeof(int));
    fout.write((char *) &(curr.input_kth), sizeof(int));
    fout.write((char *) &(curr.output), sizeof(int));
  }
  fout.flush();
  fout.close();
}

void Commands05::loadHashMapData(std::string filename, std::vector<std::pair<CompositeKey, int> >& data)
{
  std::ifstream fin(filename.c_str(), std::ios::binary);
  if(fin.good() == false){
    return;
  }

  long long len;
  fin.read((char *) &len, sizeof(long long));
  for(long long i = 0; i < len; ++i){
    std::pair<CompositeKey, int> curr;
    fin.read((char *) &(curr.first.key1), sizeof(int));
    fin.read((char *) &(curr.first.key2), sizeof(float));
    fin.read((char *) &(curr.first.key3), sizeof(int));
    fin.read((char *) &(curr.second), sizeof(int));
    data.push_back(curr);
  }
}
  
void Commands05::saveHashMapData(std::string filename, std::vector<std::pair<CompositeKey, int> >& data)
{
  std::ofstream fout(filename.c_str(), std::ios::binary);
  if(fout.good() == false){
    return;
  }

  long long len = data.size();
  fout.write((char *) &len, sizeof(long long));
  for(long long i = 0; i < len; ++i){
    std::pair<CompositeKey, int> curr = data[i];
    fout.write((char *) &(curr.first.key1), sizeof(int));
    fout.write((char *) &(curr.first.key2), sizeof(float));
    fout.write((char *) &(curr.first.key3), sizeof(int));
    fout.write((char *) &(curr.second), sizeof(int));
  }
  fout.flush();
  fout.close();
}

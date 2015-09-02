#ifndef RANDOM_H
#define RANDOM_H

#include <vector>
#include <string>

class Random {
public:
  Random();
  int nextInt(int range);
  void randomVector(int size, std::vector<int>& output);
};

#endif

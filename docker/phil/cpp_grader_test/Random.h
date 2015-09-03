#ifndef RANDOM_H
#define RANDOM_H

#include <vector>
#include <string>
#include "vector.h"

class Random {
public:
  Random();
  int nextInt(int range);
  void randomVector(int size, std::vector<int>& output);
  void randomVector(int size, vector<double>& output);
};

#endif

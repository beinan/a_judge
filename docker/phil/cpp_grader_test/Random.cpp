#include "Random.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Random::Random(){
  srand(time(NULL));
  for(int i = 0; i < 5; ++i){
    int num = nextInt(20);
    srand(num);
  }
}

int Random::nextInt(int range){
  return rand() % range;
}

void Random::randomVector(int size, std::vector<int>& output)
{
  std::vector<int> choices;
  for(int i = 0; i < size + 5; ++i){
    choices.push_back(i);
  }

  for(int i = 0; i < size; ++i){
    int index = nextInt(choices.size());
    int value = choices[index];
    output.push_back(value);
    if((size_t) index == choices.size() - 1){
      choices.pop_back();
    } else {
      int last = choices[choices.size() - 1];
      choices[index] = last;
      choices.pop_back();
    }
  }
}

void Random::randomVector(int size, vector<double>& output)
{
  std::vector<double> choices;
  for(int i = 0; i < size + 5; ++i){
    choices.push_back(i);
  }

  for(int i = 0; i < size; ++i){
    int index = nextInt(choices.size());
    double value = choices[index];
    output.push_back(value);
    if((size_t) index == choices.size() - 1){
      choices.pop_back();
    } else {
      int last = choices[choices.size() - 1];
      choices[index] = last;
      choices.pop_back();
    }
  }
}

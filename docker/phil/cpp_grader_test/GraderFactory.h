#ifndef GRADER_FACTORY_H
#define GRADER_FACTORY_H

#include "AbstractGrader.h"
#include <string>

class GraderFactory {
public:
  AbstractGrader * create(std::string assigment);
};

#endif

#include "GraderFactory.h"
#include "AbstractGrader.h"
#include <string>

#include "Grader00.h"
#include "Grader01.h"
#include "Grader02.h"
#include "Grader03.h"
#include "Grader04.h"
#include "Grader05.h"

AbstractGrader * GraderFactory::create(std::string assignment){
  if(assignment.size() == 1){
    assignment = "0" + assignment;
  }
  if(assignment == "00"){
    return new Grader00();
  } else if(assignment == "01"){
    return new Grader01();
  } else if(assignment == "02"){
    return new Grader02();
  } else if(assignment == "03"){
    return new Grader03();
  } else if(assignment == "04"){
    return new Grader04();
  } else if(assignment == "05"){
    return new Grader05();
  } else {
    return NULL;
  }
}

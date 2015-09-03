#include <string>
#include <cstring>
#include "TestCase.h"
#include "Stopwatch.h"

#include "Interfaces00.h"
#include "Grader00.h"

TestCase * Grader00::testEcho(std::string input, std::string output)
{
  IStringEcho * obj = (IStringEcho *) createObject("IStringEcho");
  if(obj == NULL){
    return nullObject("IStringEcho");
  }
  Stopwatch watch;
  std::string processed = obj->echo(input);
  watch.stop();
  
  TestCase * ret = new TestCase();
  ret->time = watch.getTime();
  
  if(processed == output){
    ret->error_message = "";
    ret->passed = true;
  } else {
    ret->error_message = std::string("expecting: ")+output+std::string(" received: ")+processed;
    ret->passed = false;
  }
  return ret;
}

TestCase * Grader00::testReverse(std::string input, std::string output)
{
  IStringReverse * obj = (IStringReverse *) createObject("IStringReverse");
  if(obj == NULL){
    return nullObject("IStringReverse");
  }
  Stopwatch watch;
  std::string processed = obj->reverse(input);
  watch.stop();
  
  TestCase * ret = new TestCase();
  ret->time = watch.getTime();
  
  if(processed == output){
    ret->error_message = "";
    ret->passed = true;
  } else {
    ret->error_message = std::string("expecting: ")+output+std::string(" received: ")+processed;
    ret->passed = false;
  }
  return ret;
}

int Grader00::size(){
  return 6;
}
  
std::string Grader00::getDescription(int test_case){
  switch(test_case){
    case 0: return "echo hello world";
    case 1: return "echo https://github.com/pcpratts/soot";
    case 2: return "echo https://github.com/pcpratts/rootbeer1";
    case 3: return "reverse hello world";
    case 4: return "reverse https://github.com/pcpratts/soot";
    case 5: return "reverse https://github.com/pcpratts/rootbeer1";
  }
  return "";
}

int Grader00::getPoints(int test_case){
  if(test_case < 5){
    return 16;
  }
  return 20;
}

Date Grader00::getDueDate(){
  return Date(9, 5, 2013);
}

TestCase * Grader00::grade(int index){
  switch(index){
  case 0: return testEcho("hello world", "hello world");
  case 1: return testEcho("https://github.com/pcpratts/soot", "https://github.com/pcpratts/soot");
  case 2: return testEcho("https://github.com/pcpratts/rootbeer1", "https://github.com/pcpratts/rootbeer1");
  case 3: return testReverse("hello world", "dlrow olleh");
  case 4: return testReverse("https://github.com/pcpratts/soot", "toos/sttarpcp/moc.buhtig//:sptth");
  case 5: return testReverse("https://github.com/pcpratts/rootbeer1", "1reebtoor/sttarpcp/moc.buhtig//:sptth");
  }
  return NULL;
}

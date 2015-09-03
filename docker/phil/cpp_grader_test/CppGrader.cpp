#include <iostream>
#include <string>
#include "AbstractGrader.h"
#include "GraderFactory.h"
#include <dlfcn.h>
#include <vector>
#include "TestCase.h"
#include "ToString.h"
#include <cstdlib>
#include <exception>
#include <sys/resource.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <stdio.h>

std::string uuid;

//http://stackoverflow.com/questions/2279052/increase-stack-size-in-linux-with-setrlimit
void bigCallStack()
{
  const rlim_t stack_size = 100L * 1024L * 1024L;
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if(result == 0){
    if (rl.rlim_cur < stack_size) {
      rl.rlim_cur = stack_size;
      setrlimit(RLIMIT_STACK, &rl);    
    }
  }
}

void catchterm(){
  std::cout << "  </program_output>" << std::endl;
  std::cout << "    <results>" << std::endl;
  std::cout << "    <result>" << std::endl;
  std::cout << "      <passed>0</passed>" << std::endl;
  std::cout << "      <error_message>catchterm (segfault or out_of_memory)</error_message>" << std::endl;
  std::cout << "      <time>0</time>" << std::endl;
  std::cout << "    </result>" << std::endl;
  std::cout << "    </results>" << std::endl;
  std::cout << "</root>" << std::endl;
  std::cout.flush();
  abort();
}

void reloadAssignments()
{
  GraderFactory factory;
  int assign_num = 0;
  std::cout << "<root>" << std::endl;
  std::cout << "<assigns>" << std::endl;
  while(true){
    std::string assign_str = toString(assign_num);
    if(assign_str.size() == 1){
      assign_str = std::string("0") + assign_str;
    }
    AbstractGrader * grader = factory.create(assign_str);
    if(grader == NULL){
      break;
    }
    ++assign_num;
    std::cout << "  <assign>" << std::endl;
    std::cout << "    <assign_num>" << assign_str << "</assign_num>" << std::endl;
    std::cout << "    <date>" << grader->getDueDate().toXmlString() << "</date>" << std::endl;
    if(grader->size() == 0){
      std::cout << "    <questions />" << std::endl;
    } else {
      std::cout << "    <questions>" << std::endl;
      for(size_t i = 0; i < grader->size(); ++i){
        std::cout << "      <question>" << std::endl;
        std::cout << "        <qnum>" << i << "</qnum>" << std::endl;
        std::cout << "        <points>" << grader->getPoints(i) << "</points>" << std::endl;
        std::cout << "        <desc>" << grader->getDescription(i) << "</desc>" << std::endl;
        std::cout << "      </question>" << std::endl;
      }
      std::cout << "    </questions>" << std::endl;
    }
    std::cout << "  </assign>" << std::endl;
    delete grader;
  }
  std::cout << "</assigns>" << std::endl;
  std::cout << "</root>" << std::endl;
}

int main(int argc, char * argv[]){

  std::set_terminate(catchterm);  
  std::set_unexpected(catchterm);
  
  std::string cmd(argv[1]);
  if(cmd == "reload_assignments"){
    reloadAssignments();
    return 0;
  }

  bigCallStack();

  std::string dll_path = std::string("/libsubmit.so");
  if(argc == 4){
    dll_path = std::string(argv[3]);
  }
  std::string assignment = std::string(argv[1]);
  std::string problem_str = std::string(argv[2]);
  int problem = atoi(problem_str.c_str());
  GraderFactory factory;
  AbstractGrader * grader = factory.create(assignment);
  if(grader == NULL){
    std::cout << "grader == NULL" << std::endl;
  }
  std::vector<TestCase *> results;

  std::cout << "<root>" << std::endl;
  std::cout << "  <pid>" << std::endl;  
  std::cout << "  " << getpid() << std::endl;
  std::cout << "  </pid>" << std::endl;
  std::cout << "  <program_output>" << std::endl;
  void * lib_handle = dlopen(dll_path.c_str(), RTLD_LAZY);
  if(lib_handle == NULL){
    std::cout << "lib_handle == NULL" << std::endl;
    std::cout << "message: " << dlerror() << std::endl;
  }

  grader->setDllHandle(lib_handle);
  //redirect stdout to null
  FILE fp_old = *stdout; 
  *stdout = *fopen("/dev/null","w");
  TestCase * result = grader->grade(problem); 
  //restore stdout
  *stdout = fp_old;  
  dlclose(lib_handle);
  std::cout << "  </program_output>" << std::endl;
  std::cout << "    <results>" << std::endl;
  std::cout << "    <result>" << std::endl;
  std::cout << "      <passed>" << result->passed << "</passed>" << std::endl;
  std::cout << "      <error_message>" << result->error_message << "</error_message>" << std::endl;
  std::cout << "      <time>" << result->time << "</time>" << std::endl;
  std::cout << "    </result>" << std::endl;
  std::cout << "    </results>" << std::endl;
  
  std::cout << "</root>" << std::endl;
  return 0;
}

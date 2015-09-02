#pragma once

#include <string>

class ObjectFactory {
public:
  ObjectFactory();
  virtual ~ObjectFactory();  
  virtual void * create(std::string interface_name) = 0;
};

extern "C" {
  ObjectFactory * createObjectFactory();
}

#include "Interfaces05.h"

void CompositeKey::operator=(const CompositeKey& rhs) {
  key1 = rhs.key1;
  key2 = rhs.key2;
  key3 = rhs.key3;
}

bool CompositeKey::operator<(const CompositeKey& rhs) const {
  if(key1 < rhs.key1){
    return true;
  } else if(key1 > rhs.key1) {
    return false;
  } else if(key2 < rhs.key2) {
    return true;
  } else if(key2 > rhs.key2) {
    return false;
  } else if(key3 < rhs.key3) {
    return true;
  } else {
    return false;
  }
}

bool CompositeKey::operator==(const CompositeKey& rhs) const {
  if(key1 == rhs.key1 &&
     key2 == rhs.key2 &&
     key3 == rhs.key3){

    return true;
  } else {
    return false;
  }
}

void CompositeKey::operator=(CompositeKey& rhs) {
  key1 = rhs.key1;
  key2 = rhs.key2;
  key3 = rhs.key3;
}

bool CompositeKey::operator<(CompositeKey& rhs) {
  if(key1 < rhs.key1){
    return true;
  } else if(key1 > rhs.key1) {
    return false;
  } else if(key2 < rhs.key2) {
    return true;
  } else if(key2 > rhs.key2) {
    return false;
  } else if(key3 < rhs.key3) {
    return true;
  } else {
    return false;
  }
}

bool CompositeKey::operator==(CompositeKey& rhs) {
  if(key1 == rhs.key1 &&
     key2 == rhs.key2 &&
     key3 == rhs.key3){

    return true;
  } else {
    return false;
  }
}

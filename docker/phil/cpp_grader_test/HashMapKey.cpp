#include "HashMapKey.h"

bool HashMapKey::operator!=(const HashMapKey& rhs) const
{
  return !this->operator==(rhs);
}

bool HashMapKey::operator!=(HashMapKey rhs)
{
  return !this->operator==(rhs);
}

bool HashMapKey::operator==(const HashMapKey& rhs) const {
  if(fname != rhs.fname){
    return false;
  }
  if(lname != rhs.lname){
    return false;
  }
  if(birth_year != rhs.birth_year){
    return false;
  }
  if(birth_month != rhs.birth_month){
    return false;
  }
  if(birth_day != rhs.birth_day){
    return false;
  }
  return true;
}  

bool HashMapKey::operator==(HashMapKey rhs) {
  if(fname != rhs.fname){
    return false;
  }
  if(lname != rhs.lname){
    return false;
  }
  if(birth_year != rhs.birth_year){
    return false;
  }
  if(birth_month != rhs.birth_month){
    return false;
  }
  if(birth_day != rhs.birth_day){
    return false;
  }
  return true;
}  

bool HashMapKey::operator<(const HashMapKey& rhs) const {
  if(lname < rhs.lname){
    return true;
  } else if(rhs.lname < lname){
    return false;
  } else {
    if(fname < rhs.fname){
      return true;
    } else if(rhs.fname < fname){
      return false;
    } else {
      if(birth_year < rhs.birth_year){
        return true;
      } else if(rhs.birth_year < birth_year){
        return false;
      } else {
        if(birth_month < rhs.birth_month){
          return true;
        } else if(rhs.birth_month < birth_month){
          return false;
        } else {
          if(birth_day < rhs.birth_day){
            return true;
          } else {
            return false;
          }
        }
      }
    }
  }
}

bool HashMapKey::operator<(HashMapKey rhs) {
  if(lname < rhs.lname){
    return true;
  } else if(rhs.lname < lname){
    return false;
  } else {
    if(fname < rhs.fname){
      return true;
    } else if(rhs.fname < fname){
      return false;
    } else {
      if(birth_year < rhs.birth_year){
        return true;
      } else if(rhs.birth_year < birth_year){
        return false;
      } else {
        if(birth_month < rhs.birth_month){
          return true;
        } else if(rhs.birth_month < birth_month){
          return false;
        } else {
          if(birth_day < rhs.birth_day){
            return true;
          } else {
            return false;
          }
        }
      }
    }
  }
}

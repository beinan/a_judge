#pragma once

#include <string>

class HashMapKey {
public:
  std::string fname;
  std::string lname;
  int birth_year;
  int birth_month;
  int birth_day;

  bool operator==(const HashMapKey& rhs) const;
  bool operator==(HashMapKey rhs);

  bool operator<(const HashMapKey& rhs) const;
  bool operator<(HashMapKey rhs);

  bool operator!=(const HashMapKey& rhs) const;
  bool operator!=(HashMapKey rhs);
};

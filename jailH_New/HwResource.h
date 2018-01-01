
#ifndef HwResource_H
#define HwResource_H

#include <map>
#include <string>
typedef unsigned long long UNS_64;

class HwResource
{
protected:
  std::string reg_name;
  UNS_64 start_addr;
  UNS_64 end_addr;
  UNS_64 size;

public:
  HwResource(const std::string &  name, UNS_64 start, UNS_64 end, UNS_64 size);
  UNS_64 get_start_addr() const;
  UNS_64 get_end_addr() const;
  UNS_64 get_size() const;
  std::string get_reg_name() const;
};

#endif

#ifndef MemRegion_H
#define MemRegion_H

#include "HwResource.h"
#include <string>
#include <vector>
#include <map>

class MemRegion
{
  std::string name;
  UNS_64 phys_start;
  UNS_64 virt_start;
  UNS_64 size;
  std::vector<std::string> flags;
	UNS_64 phys_end;
	UNS_64 virt_end;

public:
  MemRegion(std::string  in_name="", UNS_64 phys=0, UNS_64 virt=0,
            UNS_64 siz=0,std::vector<std::string>  flags={});
  UNS_64 get_phys_start() const;
  UNS_64 get_virt_start() const;
  UNS_64 get_phys_end() const;
  UNS_64 get_virt_end() const;
  UNS_64 get_size() const;
  std::string get_name() const;
  std::vector<std::string> get_flags() const;
  void printMemRegion() const;
  std::map<std::string ,std::string> FLAGS ;
};

#endif

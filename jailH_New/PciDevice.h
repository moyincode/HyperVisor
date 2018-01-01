#ifndef PciDevice_H
#define PciDevice_H

#include <string>
#include <vector>
#include "HwResource.h"

class PciDevice
{
  std::string name;
  std::string type;
  std::string shmem_protocol;
  unsigned int bdf;
  std::vector<UNS_64> bar_mask;
  int shmem_region;

public:
  PciDevice(std::string in_name="", std::string in_type="", 
      unsigned int in_bdf=0, std::vector<UNS_64> in_bar_mask={},
      int in_shmem_region=0, std::string in_shmem_protocol="");
  std::string get_name() const;
  std::string get_type() const;
  std::string get_shmem_protocol() const;
  unsigned int get_bdf() const;
  std::vector<UNS_64> get_bar_mask() const;
  int get_shmem_region() const;
};
#endif

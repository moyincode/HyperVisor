#ifndef IrqChip_H
#define IrqChip_H

#include "HwResource.h"
#include <string>
#include <vector>

class IrqChip
{
  std::string name;
  UNS_64 address;
  unsigned int pin_base;
  std::vector<UNS_64> pin_bitmap;
  
public:
  IrqChip(std::string in_name="", UNS_64 in_address=0, 
          int in_pin_base =0, std::vector<UNS_64> in_pin_bitmap={});
  std::string get_name() const;
  UNS_64 get_address() const;
  unsigned int get_pin_base() const;
  std::vector<UNS_64> get_pin_bitmap() const;
  void printIrqChip() const;  
};

#endif

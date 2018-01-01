/*
 * Module for IRQ-chip configuration
 *
 *  Author :
 *
 *  Copyright (C) 2017 , All Rights Reserved.
 */

#include "IrqChip.h"
#include <iostream>

IrqChip::IrqChip(std::string in_name, UNS_64 in_address, 
          int in_pin_base, std::vector<UNS_64> in_pin_bitmap):
            name(in_name), address(in_address), pin_base(in_pin_base),
            pin_bitmap(in_pin_bitmap)
{}

std::string IrqChip::get_name() const
{
  return name;  
}

UNS_64 IrqChip::get_address() const
{
  return address;
}

unsigned int IrqChip::get_pin_base() const
{
  return pin_base;
}
 
std::vector<UNS_64> IrqChip::get_pin_bitmap() const
{
  return pin_bitmap;
}

void IrqChip::printIrqChip() const
{
  std::cout << "IrqChip info \n";
  std::cout << " \t name = " << name << '\n';
  std::cout << " \t address = " << address << '\n';
  std::cout << " \t pin_base = " << pin_base << '\n';
  std::cout << " \t pin_bitmap = {" <<  '\n';
  for ( const auto & bitmap : pin_bitmap) 
      std::cout << " \t\t " << bitmap << '\n';
  std::cout << "}\n";
}

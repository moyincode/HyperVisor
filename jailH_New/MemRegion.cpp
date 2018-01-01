/*
 * Module for Memory region configuration
 *
 *  Author :
 *
 *  Copyright (C) 2017 , All Rights Reserved.
 */


#include "MemRegion.h"
#include <iostream>
#include <vector>
#include "J_error.h"

MemRegion::MemRegion(std::string  in_name, UNS_64 phys, UNS_64 virt,
                      UNS_64 siz, std::vector<std::string>  in_flags)
                    : name(in_name), phys_start(phys), virt_start(virt), 
                       size(siz), flags(in_flags)
{
	phys_end = phys_start + size;
	virt_end = virt_start + size;
  if(size == 0 )
  {
    std::string error_msg = "MemRegion : " + name + " size can not be zero";
    throw J_error(error_msg.c_str());
  }
}

UNS_64 MemRegion::get_phys_start() const
{
  return phys_start;
}

UNS_64 MemRegion::get_virt_start() const
{
  return virt_start;
}

UNS_64 MemRegion::get_size() const
{
  return size;
}

std::string MemRegion::get_name() const
{
  return name;
}

std::vector<std::string> MemRegion::get_flags() const
{
  return flags;
}

void MemRegion::printMemRegion() const
{
  std::cout << " MemRegion info : \n";
  std::cout << " \t name = " << name << '\n';
  std::cout << " \t Physical address start = " << phys_start << '\n';
  std::cout << " \t virtual address start = " << virt_start << '\n';
  std::cout << " \t size = " << size << '\n';
//  std::cout << " \t flags = " << flags << '\n';
}

UNS_64 MemRegion::get_phys_end() const
{
  return phys_end;
}

UNS_64 MemRegion::get_virt_end() const
{
  return virt_end;
}

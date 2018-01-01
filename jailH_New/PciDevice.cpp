/*
 * Module for PCI Device configuration
 *
 *  Author :
 *
 *  Copyright (C) 2017 , All Rights Reserved.
 */

#include "PciDevice.h"
#include <iostream>


PciDevice::PciDevice(std::string in_name, std::string in_type, 
      unsigned int in_bdf, std::vector<UNS_64> in_bar_mask,
      int in_shmem_region, std::string in_shmem_protocol):
      name(in_name),type(in_type),bdf(in_bdf),bar_mask(in_bar_mask),
      shmem_region(in_shmem_region),shmem_protocol(in_shmem_protocol)
{}

std::string PciDevice::get_name() const
{
  return name;
}

std::string PciDevice::get_type() const
{
  return type;
}

std::string PciDevice::get_shmem_protocol() const
{
  return shmem_protocol;
}

unsigned int PciDevice::get_bdf() const
{
  return bdf;
}

std::vector<UNS_64> PciDevice::get_bar_mask() const
{
  return bar_mask;
}

int PciDevice::get_shmem_region() const
{
  return shmem_region;
}



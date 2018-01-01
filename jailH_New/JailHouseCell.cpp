/*
 * Module for JailHouseCell configuration
 *
 *  Author :
 *
 *  Copyright (C) 2017 , All Rights Reserved.
 */

#include <iostream>
#include "JailHouseCell.h"

extern int CORE ;

JailHouseCell::JailHouseCell(const std::string & name):cellname(name)
{
    for (int i=0; i<CORE; i++)
        cpuIds[i] = false ;
}

// To add a pci_device instance to JailHouse cell map
void JailHouseCell::add_pci(const PciDevice & pci)
{
  auto success = pci_map.insert(std::pair<unsigned int,PciDevice>( pci.get_bdf(),pci ));
  if(!success.second)
  {
    auto pci_name = ((success.first)->second).get_name();

    std::string error_msg = " insert failed pci bdf =" + 
                              std::to_string(pci.get_bdf());
    error_msg = error_msg + " already used for " + pci_name+"\n" ;

    throw JailHouseCell_error(error_msg.c_str());
    return;
  }
}

// To remove a pci_device instance from JailHouse cell map
void JailHouseCell::delete_pci(const std::string & pci_name)
{
  for(auto & elem : pci_map)
  {
    auto pci = elem.second;
    if( pci.get_name() == pci_name )
    {
      pci_map.erase(elem.first);
      std::cout << "delete successful for " << pci_name << "\n";
      return;
    }
  } 
  std::cout << pci_name  << " is not present in pci_map \n";
}

// To add a memory region instance to JailHouse cell map
void JailHouseCell::add_memRegion(const MemRegion & memRegion)
{      
	auto mem_it = find_mem_overlap(memRegion);
	if( mem_it != get_memRegionItr_end() )
	{
		std::string error_msg = "address overlap for the MemRegion " + memRegion.get_name();
		error_msg = "  with the MemRegion " + (mem_it->second).get_name() + '\n';
    throw JailHouseCell_error(error_msg.c_str());
	}
  auto success = memRegion_map.insert(std::pair<UNS_64, MemRegion>
                        (memRegion.get_phys_start(),memRegion ));
  if(!success.second)
  {
    auto memRegion_name = ((success.first)->second).get_name();
    std::string error_msg = "insert failed: start_address"+ 
                            std::to_string(memRegion.get_phys_start());
    error_msg = error_msg + " already used for " + memRegion_name+ "\n" ;
    throw JailHouseCell_error(error_msg.c_str());
  }
}

// To remove a memory region instance from JailHouse cell map
void JailHouseCell::delete_memRegion(const std::string & name)
{
  for(auto & elem : memRegion_map)
  {
    auto memRegion = elem.second;
    if( memRegion.get_name() == name )
    {
      memRegion_map.erase(elem.first);
      std::cout << "delete successful for " << name << "\n";
      return;
    }
  } 
  std::cout << name  << " is not present in memRegion_map \n";
}

// To add a irq-chip instance to JailHouse cell map
void JailHouseCell::add_irqChip(const IrqChip & irqChip)
{
  auto success = irqChip_map.insert(std::pair<unsigned int, IrqChip>
                        ( irqChip.get_pin_base(), irqChip) );  
  if(!success.second)
  {
    auto irqChip_name = ((success.first)->second).get_name();
    std::string error_msg = "insert failed pin_base = " + 
                            std::to_string(irqChip.get_pin_base());
    error_msg = error_msg + " already used for " + irqChip_name + "\n" ;
    throw JailHouseCell_error(error_msg.c_str());
  }
}

// To remove a irq-chip instance from JailHouse cell map
void JailHouseCell::delete_irqChip(const std::string & name)
{
  for(auto & elem : irqChip_map)
  {
    auto irqChip = elem.second;
    if( irqChip.get_name() == name )
    {
      memRegion_map.erase(elem.first);
      std::cout << "delete successful for " << name << "\n";
      return;
    }
  } 
  std::cout << name  << " is not present in memRegion_map \n";
}


std::string JailHouseCell::get_name() const
{
  return cellname;
}

void JailHouseCell::set_cpuIds(std::vector<bool> in_cpuIds)
{
  if(in_cpuIds.size() != CORE )
    throw 20;
  for(int i = 0; i < CORE ; ++i)
    cpuIds[i] = in_cpuIds[i];

}

void JailHouseCell::set_cpuIds(int pos, bool value)
{
  if( pos < 0 || pos > 5)
    throw 20;
  cpuIds[pos] = value;
}

const std::map<UNS_64, MemRegion>::iterator JailHouseCell::get_memRegionItr_begin()
{
  return memRegion_map.begin();
}

const std::map<UNS_64, MemRegion>::iterator JailHouseCell::get_memRegionItr_end()
{
  return memRegion_map.end();
}

const std::map<unsigned int, PciDevice>::iterator JailHouseCell::get_pciDeviceItr_begin()
{
  return pci_map.begin();
}

const std::map<unsigned int, PciDevice>::iterator JailHouseCell::get_pciDeviceItr_end()
{
  return pci_map.end();
}

const std::map<unsigned int, IrqChip>::iterator JailHouseCell::get_irqChipItr_begin()
{
  return irqChip_map.begin();
}

const std::map<unsigned int, IrqChip>::iterator JailHouseCell::get_irqChipItr_end()
{
  return irqChip_map.end();
}

// To print jailHouse cell info for debugging purpose
void JailHouseCell::print_JailHouseCell() const
{
  std::cout << " Jail house cell info \n";
  std::cout << " cell name = " << cellname << '\n';
  for ( auto & memr : memRegion_map)
    (memr.second).printMemRegion();
  for ( auto & irqc : irqChip_map)
    (irqc.second).printIrqChip();
}


// validating overlap between memory regions, skipping "RAM" memory region.
const std::map<UNS_64, MemRegion>::iterator JailHouseCell::find_mem_overlap(
                                                            const MemRegion & in_mem)
{      
    if( in_mem.get_name() == "RAM")
       return get_memRegionItr_end();
	auto mem_it = get_memRegionItr_begin();
	for( ; mem_it != get_memRegionItr_end()
		; ++mem_it)
	{
		MemRegion mem = mem_it->second;
        if(mem.get_name() == "RAM")
              continue;
		if(( in_mem.get_phys_start() >= mem.get_phys_start() )
			&&  ( in_mem.get_phys_start() < mem.get_phys_end() ))
			return mem_it;
		
		if(( in_mem.get_phys_end() > mem.get_phys_start() )
			&&  ( in_mem.get_phys_end() <= mem.get_phys_end() ))
			return mem_it;
		
		if(( in_mem.get_virt_start() >= mem.get_virt_start() )
			&&  ( in_mem.get_virt_start() < mem.get_virt_end() ))
			return mem_it;
		
		if(( in_mem.get_virt_end() >= mem.get_virt_start() )
			&&  ( in_mem.get_virt_end() < mem.get_virt_end() ))
			return mem_it;
	}
	return mem_it;
}

const std::map<unsigned int, PciDevice>::iterator JailHouseCell::find_pci_ovelap(
																										const PciDevice & in_pci)
{
	 return  pci_map.find(in_pci.get_bdf()); 
}

const std::map<unsigned int, IrqChip>::iterator JailHouseCell::find_irq_ovelap(
																										const IrqChip & in_irq)
{
	return irqChip_map.find(in_irq.get_pin_base());
}

std::vector<bool> JailHouseCell::get_cpuIds()
{
  std::vector<bool> cpu_vec;
  for(int i = 0 ; i <CORE ; ++i)
    cpu_vec.push_back(cpuIds[i]);
  return cpu_vec;
}

int JailHouseCell::get_cpu_count() const
{
	int count=0;
  for(int i = 0 ; i <CORE ; ++i)
    if(cpuIds[i])
			++count;
	return count;
}

int JailHouseCell::get_mem_Regioncount() const
{
	return memRegion_map.size();
}
		
int JailHouseCell::get_pcicount() const
{
	pci_map.size();
}

int JailHouseCell::get_irqcount() const
{
	irqChip_map.size();
}

std::string  JailHouseCell::get_signature() const
{
  return signature;
}

void  JailHouseCell::set_signature(std::string in_signature)
{
  signature = in_signature;
}
  
std::string  JailHouseCell::get_revision() const
{
  return revision;
}

void  JailHouseCell::set_revision(std::string in_revision)
{
  revision = in_revision;
}

std::vector<std::string>  JailHouseCell::get_flags() const
{
  return flags;
}

void  JailHouseCell::set_flags(std::vector<std::string> in_flags)
{
  flags = in_flags;
}

int  JailHouseCell::get_vpci_irq_base() const
{
  return vpci_irq_base;
}

void  JailHouseCell::set_vpci_irq_base(int in_vpci_irq_base)
{
  vpci_irq_base = in_vpci_irq_base;
}

JailHouseCell::~JailHouseCell(){}

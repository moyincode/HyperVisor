/*
 * Module for maintaining jailHouse cell list
 *
 *  Author :
 *
 *  Copyright (C) 2017 , All Rights Reserved.
 */

#include "JailHouseCellList.h"
#include <iostream>

// To get a jailHouse cellList instance
JailHouseCellList& JailHouseCellList::getJailHouseCellList()
{
  static JailHouseCellList * jhl = new JailHouseCellList;
  return * jhl;
}

// Adding a cell to the JailHouse cellList
bool JailHouseCellList::add_cell(JailHouseCell & cell)
{
  if(RootCell * j = dynamic_cast<RootCell * >(&cell))
    return add_rootcell(*j);
  else
  {
    auto it = cell_map.find(cell.get_name());
    if( it != cell_map.end() )
    {
      std::string error_msg = "add_cell failed" + cell.get_name() 
        + " JailHouseCell is already present\n";
      throw JailHouseCell_error(error_msg.c_str());
      return false;  
    }
    else
    {
      // function to check if there is a overlap 
      // on any of the memory regions
      // check_pci_map(), check_mem_region()
      // if all are pass then add it to cell_map
      validate_cell( cell );
      cell_map.insert(std::pair<std::string, JailHouseCell>
          (cell.get_name(), cell));
      std::cout <<  cell.get_name() << " JailHouseCell is added\n";
      return true;
    }
  }

}


// Adding a cell to the jailHouse cellList without validation
bool JailHouseCellList::add_cell_no_validation(JailHouseCell & cell)
{
  if(RootCell * j = dynamic_cast<RootCell * >(&cell))
    return add_rootcell_no_validation(*j);
  else
  {
    auto it = cell_map.find(cell.get_name());
    if( it != cell_map.end() )
    {
      std::string error_msg = "add_cell failed" + cell.get_name() 
        + " JailHouseCell is already present\n";
      throw JailHouseCell_error(error_msg.c_str());
      return false;  
    }
    else
    {
      cell_map.insert(std::pair<std::string, JailHouseCell>
          (cell.get_name(), cell));
      std::cout <<  cell.get_name() << " JailHouseCell is added\n";
      return true;
    }
  }
}


// Validating memory regions, irq_chips and pci devices addressess
void JailHouseCellList::validate_cell( JailHouseCell & cell)
{
  check_mem_region(cell);
  check_pci_device(cell);
  check_irq_chip(cell);
  check_cpuids(cell);
}

// To check overlapping addresses for irq_chips across the cells
void JailHouseCellList::check_irq_chip(JailHouseCell & in_cell)
{
  auto cell_it = get_JailHouseCellItr_begin();
  for(; cell_it != get_JailHouseCellItr_end(); ++cell_it)
  {
    if(in_cell.get_name() == (cell_it->second).get_name())
      continue;
    auto irq_it =  (cell_it->second).get_irqChipItr_begin();
    for(;irq_it != (cell_it->second).get_irqChipItr_end(); ++irq_it)
    {
      auto irq_over_it = in_cell.find_irq_ovelap((irq_it->second));
      if( irq_over_it != in_cell.get_irqChipItr_end())
      {
        std::string error_msg = "bdf overlap for the IrqChip " + (irq_it->second).get_name();
        error_msg = error_msg + " with IrqChip " + (irq_over_it->second).get_name();
        error_msg = error_msg + " of cell " + cell_it->first + '\n'; 
        throw JailHouseCell_error(error_msg.c_str());
      }
    }
  }
  if(RootCell * j = dynamic_cast<RootCell * >(&in_cell))
  {
    return;
  }
  else
  {
    auto irq_it =  (rootcell).get_irqChipItr_begin();
    for(;irq_it != (rootcell).get_irqChipItr_end(); ++irq_it)
    {
      auto irq_over_it = in_cell.find_irq_ovelap((irq_it->second));
      if( irq_over_it != in_cell.get_irqChipItr_end())
      {
        std::string error_msg = "bdf overlap for the IrqChip " + (irq_it->second).get_name();
        error_msg = error_msg + " with IrqChip " + (irq_over_it->second).get_name();
        error_msg = error_msg + " of cell " + rootcell.get_name() + '\n'; 
        throw JailHouseCell_error(error_msg.c_str());
      }
    }
  }
}

// To check overlapping addresses for pci_devices across the cells
void JailHouseCellList::check_pci_device(JailHouseCell & in_cell)
{
  auto cell_it = get_JailHouseCellItr_begin();
  for(; cell_it != get_JailHouseCellItr_end(); ++cell_it)
  {
    if(in_cell.get_name() == (cell_it->second).get_name())
      continue;
    auto pci_it =  (cell_it->second).get_pciDeviceItr_begin();
    for(;pci_it != (cell_it->second).get_pciDeviceItr_end(); ++pci_it)
    {
      auto pci_over_it = in_cell.find_pci_ovelap((pci_it->second));
      if( pci_over_it != in_cell.get_pciDeviceItr_end())
      {
        std::string error_msg = "bdf overlap for the PciDevice " + (pci_it->second).get_name();
        error_msg = error_msg + " with PciDevice " + (pci_over_it->second).get_name();
        error_msg = error_msg + " of cell " + cell_it->first + '\n'; 
        throw JailHouseCell_error(error_msg.c_str());
      }
    }
  }
  if(RootCell * j = dynamic_cast<RootCell * >(&in_cell))
  {
    return;
  }
  else
  {
    auto pci_it =  (rootcell).get_pciDeviceItr_begin();
    for(;pci_it != (rootcell).get_pciDeviceItr_end(); ++pci_it)
    {
      auto pci_over_it = in_cell.find_pci_ovelap((pci_it->second));
      if( pci_over_it != in_cell.get_pciDeviceItr_end())
      {
        std::string error_msg = "bdf overlap for the PciDevice " + (pci_it->second).get_name();
        error_msg = error_msg + " with PciDevice " + (pci_over_it->second).get_name();
        error_msg = error_msg + " of cell " + rootcell.get_name() + '\n'; 
        throw JailHouseCell_error(error_msg.c_str());
      }
    }
  }
}


// To check overlapping addresses for memory-regions across the cells
void JailHouseCellList::check_mem_region(JailHouseCell & in_cell)
{
  auto cell_it = get_JailHouseCellItr_begin();  
  for(; cell_it != get_JailHouseCellItr_end(); ++cell_it)
  {
    if(in_cell.get_name() == (cell_it->second).get_name())
      continue;
    auto mem_it =  (cell_it->second).get_memRegionItr_begin();
    for(;mem_it != (cell_it->second).get_memRegionItr_end(); ++mem_it)
    {
      auto mem_over_it = in_cell.find_mem_overlap((mem_it->second));
      if( mem_over_it != in_cell.get_memRegionItr_end())
      {
        std::string error_msg = "address overlap for the MemRegion " + (mem_it->second).get_name();
        error_msg = error_msg + " with MemRegoion " + (mem_over_it->second).get_name();
        error_msg = error_msg + " of cell " + cell_it->first + '\n'; 
        throw JailHouseCell_error(error_msg.c_str());
      }
    }
  }
  if(RootCell * j = dynamic_cast<RootCell * >(&in_cell))
  {
    return;
  }
  else
  {
    auto mem_it = rootcell.get_memRegionItr_begin();
    for(;mem_it != rootcell.get_memRegionItr_end(); ++mem_it)
    {
      auto mem_over_it = in_cell.find_mem_overlap((mem_it->second));
      if( mem_over_it != in_cell.get_memRegionItr_end())
      {
        std::string error_msg = "address overlap for the MemRegion " + (mem_it->second).get_name();
        error_msg = error_msg + " with MemRegoion " + (mem_over_it->second).get_name();
        error_msg = error_msg + " of cell " + rootcell.get_name() + '\n'; 
        throw JailHouseCell_error(error_msg.c_str());
      }
    }
  }
}

// To check overlapping CPU id's across the cells
void JailHouseCellList::check_cpuids( JailHouseCell & in_cell)
{
  auto cell_it = get_JailHouseCellItr_begin();
  auto in_cpu_vec = in_cell.get_cpuIds();
  for(; cell_it != get_JailHouseCellItr_end(); ++cell_it)
  {
    if(in_cell.get_name() == (cell_it->second).get_name())
      continue;
    auto cpu_vec = (cell_it->second).get_cpuIds();
    for(int i = 0 ; i < cpu_vec.size() ; ++i)
    {
      if( (cpu_vec[i] == in_cpu_vec[i]) && cpu_vec[i] )
      {
        std::string error_msg = "cpu " + std::to_string(i)
                + " already used for cell " 
                +(cell_it->second).get_name() + '\n'; 
        throw JailHouseCell_error(error_msg.c_str());
      }
    }

  }
  if(RootCell * j = dynamic_cast<RootCell * >(&in_cell))
  {
    return;
  }
  else
  {
    auto cpu_vec = get_rootcell().get_cpuIds();
    for(int i = 0 ; i < cpu_vec.size() ; ++i)
    {
      if( (cpu_vec[i] == in_cpu_vec[i]) && cpu_vec[i] )
      {
        std::string error_msg = "cpu " + std::to_string(i)
                + " already used for cell " 
                +  rootcell.get_name() + '\n';     
        throw JailHouseCell_error(error_msg.c_str());
      }
    }
    
  }
}

  const std::map<std::string, JailHouseCell>::iterator
JailHouseCellList::get_JailHouseCellItr_begin()
{
  return cell_map.begin();  
}

  const std::map<std::string, JailHouseCell>::iterator
JailHouseCellList::get_JailHouseCellItr_end()
{
  return cell_map.end();  
}

void JailHouseCellList::delete_cell (std::string cell_name) {
  int x = cell_map.erase(cell_name) ;
  std::cout << "no. of cells erased =" << x << std::endl;
}

void JailHouseCellList::delete_all (JailHouseCellList &J) {

    /*for(auto it = J.get_JailHouseCellItr_begin(); it != J.get_JailHouseCellItr_end(); ++it) {

            J.cell_map.erase(it->first)
      } */
    J.cell_map.clear();



}

int JailHouseCellList::get_number_of_cells()const {
    return cell_map.size() ;
}
bool JailHouseCellList::add_rootcell(RootCell & cell)
{
  validate_cell( cell );
  rootcell = cell;
  return true;
}

bool JailHouseCellList::add_rootcell_no_validation(RootCell & cell)
{
  rootcell = cell;
  return true;
}

RootCell JailHouseCellList::get_rootcell()
{
  return rootcell;
}

bool JailHouseCellList::Is_In_List (std::string s) {

         if  (cell_map.count(s) > 0)
             return true ;
         else
             return false ;

}

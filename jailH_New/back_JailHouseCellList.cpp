#include "JailHouseCellList.h"
#include <iostream>


JailHouseCellList& JailHouseCellList::getJailHouseCellList()
{
  static JailHouseCellList * jhl = new JailHouseCellList;
  return * jhl;
}

bool JailHouseCellList::add_cell(JailHouseCell & cell)
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
    check_mem_region(cell);
    check_pci_device(cell);
    check_irq_chip(cell);
    cell_map.insert(std::pair<std::string, JailHouseCell>
        (cell.get_name(), cell));
    std::cout <<  cell.get_name() << " JailHouseCell is added\n";
    return true;
  }

}

void JailHouseCellList::check_irq_chip(JailHouseCell & in_cell)
{
  auto cell_it = get_JailHouseCellItr_begin();
  for(; cell_it != get_JailHouseCellItr_end(); ++cell_it)
  {
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

void JailHouseCellList::check_pci_device(JailHouseCell & in_cell)
{
  auto cell_it = get_JailHouseCellItr_begin();
  for(; cell_it != get_JailHouseCellItr_end(); ++cell_it)
  {
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

void JailHouseCellList::check_mem_region(JailHouseCell & in_cell)
{
  auto cell_it = get_JailHouseCellItr_begin();
  for(; cell_it != get_JailHouseCellItr_end(); ++cell_it)
  {
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

int JailHouseCellList::get_number_of_cells()const {
    return cell_map.size() ;
}
bool JailHouseCellList::add_rootcell(RootCell & cell)
{
  check_mem_region(cell);
  check_pci_device(cell);
  check_irq_chip(cell);
  rootcell = cell;
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

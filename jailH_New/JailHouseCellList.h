#ifndef JailHouseCellList_H
#define JailHouseCellList_H

#include "PciDevice.h"
#include <map>
#include <string>
#include "JailHouseCell.h"
#include "RootCell.h"

class JailHouseCellList
{
  std::map<std::string, JailHouseCell> cell_map; 
  RootCell rootcell;
  JailHouseCellList(){};
  JailHouseCellList(const JailHouseCellList &old){}; // disallow cop constructor
  const JailHouseCellList &operator=(const JailHouseCellList &old){};//disallow assignment operator
  ~JailHouseCellList(){}; 

public:
  static JailHouseCellList& getJailHouseCellList();
  bool add_cell(JailHouseCell & cell);
  const std::map<std::string, JailHouseCell>::iterator get_JailHouseCellItr_begin();
  const std::map<std::string, JailHouseCell>::iterator get_JailHouseCellItr_end();
  void check_mem_region( JailHouseCell & in_cell);
  void check_pci_device( JailHouseCell & in_cell);
  void check_irq_chip( JailHouseCell & in_cell);
  void check_cpuids( JailHouseCell & in_cell);
  void validate_cell( JailHouseCell & in_cell);
  void delete_cell (std::string cell_name) ;
  void delete_all (JailHouseCellList &J) ;
  bool add_rootcell(RootCell & cell);
  bool add_rootcell_no_validation(RootCell & cell);
  bool add_cell_no_validation(JailHouseCell & cell);
  RootCell get_rootcell();
  int get_number_of_cells()const;
  bool Is_In_List (std::string s);
};

#endif

#ifndef RootCell_H
#define RootCell_H

#include "JailHouseCell.h"

struct Hypervisor_Memory
{
  UNS_64 phys_start;
  UNS_64 size;
};

struct Debug_Console
{
  UNS_64 address;
  UNS_64 size;
  std::vector<std::string> flags;
};

struct Platform_Info
{
  UNS_64 pci_mmconfig_base;
  int pci_mmconfig_end_bus;
  int pci_is_virtual;
  int gic_version;
  UNS_64 gicd_base;
  UNS_64 gicc_base;
  UNS_64 gich_base;
  UNS_64 gicv_base;
  int maintenance_irq;
};

class RootCell: public JailHouseCell
{
  Hypervisor_Memory hypervisor_memory;
  Debug_Console debug_console;
  Platform_Info platform_info;
  public:
  RootCell(const std::string & name=""):JailHouseCell(name){
   //   for (int i = 0; i<6; i++) {
   //       this->[i] = false ;
   //   }
  }
  Hypervisor_Memory get_Hypervisor_Memory()const;
  Debug_Console get_Debug_Console()const;
  Platform_Info get_Platform_Info()const;
  void set_Hypervisor_Memory(Hypervisor_Memory & hvm);
  void set_Debug_Console(Debug_Console & dc);
  void set_Platform_Info(Platform_Info & pi);
  virtual ~RootCell();
};

#endif

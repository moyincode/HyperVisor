#ifndef JailHouseCell_H
#define JailHouseCell_H

#include <map>
#include <string.h>
#include <vector>
#include "MemRegion.h"
#include "PciDevice.h"
#include "IrqChip.h"
#include "J_error.h"

extern int CORE ;
class JailHouseCell
{
//  static const int size_cpuid = 12 ;
  std::string cellname;
  std::map<unsigned int, PciDevice> pci_map;   // bdf as key
  std::map<UNS_64, MemRegion> memRegion_map;   // address as key
  std::map<unsigned int, IrqChip> irqChip_map; // pin_base as key
  bool cpuIds[12] ;
  
  std::string signature;
  std::string revision;
  std::vector<std::string> flags;
  int vpci_irq_base;

  public:
  JailHouseCell(const std::string &  name="");
  void add_pci(const PciDevice & pci);
  void delete_pci(const std::string & pci_name);
  void add_memRegion(const MemRegion & memRegion);
  void delete_memRegion(const std::string & name);
  void add_irqChip(const IrqChip & irqChip);
  void delete_irqChip(const std::string & name);
  std::string get_name() const;
  
  std::string get_signature() const;
  void set_signature(std::string in_signature);
  std::string get_revision() const;
  void set_revision(std::string in_revision) ;
  std::vector<std::string> get_flags() const;
  void set_flags(std::vector<std::string> in_flags);
  int get_vpci_irq_base() const;
  void set_vpci_irq_base(int v_vpci_irq_base);

  void set_cpuIds(std::vector<bool> in_cpuIds);
  void set_cpuIds(int pos, bool value);
  std::vector<bool> get_cpuIds() ;
  const std::map<UNS_64, MemRegion>::iterator get_memRegionItr_begin();
  const std::map<UNS_64, MemRegion>::iterator get_memRegionItr_end();
  const std::map<unsigned int, PciDevice>::iterator get_pciDeviceItr_begin();
  const std::map<unsigned int, PciDevice>::iterator get_pciDeviceItr_end();
  const std::map<unsigned int, IrqChip>::iterator get_irqChipItr_begin();
  const std::map<unsigned int, IrqChip>::iterator get_irqChipItr_end();
  void print_JailHouseCell() const;
  const std::map<UNS_64, MemRegion>::iterator find_mem_overlap(const MemRegion & in_mem);
  const std::map<unsigned int, PciDevice>::iterator find_pci_ovelap(const PciDevice & in_pci);
  const std::map<unsigned int, IrqChip>::iterator find_irq_ovelap(const IrqChip & in_irq);
  int get_cpu_count() const;
  int get_mem_Regioncount() const;
  int get_pcicount() const;
  int get_irqcount() const;
  virtual ~JailHouseCell();
};

DEFINE_EXCEPTION(JailHouseCell_error,"exception in JailHouseCell Class")

#endif

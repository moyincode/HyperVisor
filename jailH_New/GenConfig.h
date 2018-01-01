#ifndef GenConfig_H
#define GenConfig_H

#include "JailHouseCell.h"

class GenConfig
{
  public:
    GenConfig(JailHouseCell &j);
    ~GenConfig();
  private:
    FILE * pf;
    void writeFile(JailHouseCell &j);
    void write_mem_region(MemRegion &m);
    void write_pci_device(PciDevice &pci);
    void write_irq_chip(IrqChip &irq);
    std::string  vec_to_hex(std::vector<bool> vec) const;
    std::string getHexStr(UNS_64 n)const;
    std::string hexVecToString( std::vector<UNS_64> &vec) const;
    GenConfig();

};

#endif

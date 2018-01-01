#ifndef ReadDmp_H
#define ReadDmp_H

#ifndef NUMBER_OF_CPU
#define NUMBER_OF_CPU CORE
#endif

#include "../JailHouseCell.h"
#include "../RootCell.h"
#include <stdio.h>
#include "types.h"
#include "cell-config.h"
#include <stdlib.h>
#include <string.h>

class ReadDmp
{
  JailHouseCell * cell;
  std::string cell_name;
  int mem_count;
  int irq_count;
  int pci_count;
  int cpu_count;
  bool root;
  char * p_buffer;
  char * dmp_buffer;

  ReadDmp();
  void  add_jailhouse_system();
  void  add_jailhouse_cell_desc();
  void  add_jailhouse_memory();
  void  add_jailhouse_irqchip();
  void  add_jailhouse_pci_device();
  void  add_cpus();
  void  get_config_info(std::string & info_file);
  void  get_dumped_obj(std::string & dump_file);
  Hypervisor_Memory get_Hypervisor_Memory(const jailhouse_system * p_js);
  Debug_Console  get_Debug_Console(const jailhouse_system * p_js);
  Platform_Info  get_Platform_Info(const jailhouse_system * p_js);
  public:
  ReadDmp(std::string info_file, std::string dump_file);
  JailHouseCell * get_cell();
  ~ReadDmp();
};

DEFINE_EXCEPTION(ReadDmp_error,"exception in ReadDmp Class")
#endif

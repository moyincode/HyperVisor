#ifndef cell_type_util_H
#define cell_type_util_H

#include "types.h"
#include "cell-config.h"
#include <string>
#include <vector>

std::string get_pci_type(__u8 type);


std::string get_shemem_protocol(__u16 protocol);


template<typename C, typename T>
T combine(C c, T t);


std::vector<std::string> get_debug_console_flags(__u16 flag, __u64 address);

std::vector<std::string> get_mem_region_flags( __u16 flag );

std::string get_revision(__u16 rev);

std::vector<std::string> get_cell_desc_flags( __u64 flag);
#endif //cell_type_util_H

#include "cell_type_util.h"

std::string get_pci_type(__u8 type)
{
  
  if(type == JAILHOUSE_PCI_TYPE_DEVICE)
    return "JAILHOUSE_PCI_TYPE_DEVICE";
  else if(type == JAILHOUSE_PCI_TYPE_BRIDGE)
    return "JAILHOUSE_PCI_TYPE_BRIDGE";
  else if(type == JAILHOUSE_PCI_TYPE_IVSHMEM)
    return "JAILHOUSE_PCI_TYPE_IVSHMEM";
  else
    "UNKNOWN FLAG"; //error
}

std::string get_shemem_protocol(__u16 protocol)
{
  if( protocol == JAILHOUSE_SHMEM_PROTO_UNDEFINED)
    return "JAILHOUSE_SHMEM_PROTO_UNDEFINED";
  else if( protocol == JAILHOUSE_SHMEM_PROTO_VETH )
    return "JAILHOUSE_SHMEM_PROTO_VETH";
  else if ( protocol == JAILHOUSE_SHMEM_PROTO_CUSTOM)
    return "JAILHOUSE_SHMEM_PROTO_CUSTOM";
  else
    "UNKNOWN FLAG";//error
}

std::string get_revision(__u16 rev)
{
  if( rev == 5 )
    return "JAILHOUSE_CONFIG_REVISION";
  else
  return "JAILHOUSE_CONFIG_REVISION_x";
}

template<typename C, typename T>
T combine(C c, T t)
{
  T x;
  int size = c.size();
  if(size == 0 )
    return x;
  int i = 1;
  for (auto elm : c)
  {
    if( i == size)
      x = x + elm;
    else
      x = x + elm + t;
    ++i;
  }
  return x;
}

std::vector<std::string> get_debug_console_flags(__u16 flag, __u64 address)
{
  __u16 part_flag;
  std::vector<std::string> flags;

  part_flag = flag & 0x000f;
  if( part_flag == JAILHOUSE_CON1_TYPE_NONE )
      flags.push_back("JAILHOUSE_CON1_TYPE_NONE");
  else if( part_flag == JAILHOUSE_CON1_TYPE_VGA)
    flags.push_back("JAILHOUSE_CON1_TYPE_VGA");
  else if( part_flag == JAILHOUSE_CON1_TYPE_8250 )
    flags.push_back("JAILHOUSE_CON1_TYPE_8250");
  else if( part_flag == JAILHOUSE_CON1_TYPE_PL011)
    flags.push_back("JAILHOUSE_CON1_TYPE_PL011");
  else if( part_flag == JAILHOUSE_CON1_TYPE_XUARTPS)
    flags.push_back("JAILHOUSE_CON1_TYPE_XUARTPS");
  else if( part_flag == JAILHOUSE_CON1_TYPE_MASK)
    flags.push_back("JAILHOUSE_CON1_TYPE_MASK");
  else
    flags.push_back("UNKNOWN FLAG");//error

  part_flag = flag & 0x0010;
  if ( part_flag == JAILHOUSE_CON1_ACCESS_PIO )
    flags.push_back("JAILHOUSE_CON1_ACCESS_PIO");
  else
    flags.push_back("JAILHOUSE_CON1_ACCESS_MMIO");

  part_flag = flag & 0x0020;
  if ( part_flag == JAILHOUSE_CON1_REGDIST_1 )
    flags.push_back("JAILHOUSE_CON1_REGDIST_1");
  else
    flags.push_back("JAILHOUSE_CON1_REGDIST_4");

  part_flag = flag & 0x0f00;
  if ( part_flag == JAILHOUSE_CON2_TYPE_ROOTPAGE )
    flags.push_back("JAILHOUSE_CON2_TYPE_ROOTPAGE");
  else if (part_flag == JAILHOUSE_CON2_TYPE_MASK )
    flags.push_back("JAILHOUSE_CON2_TYPE_MASK");
  else
    flags.push_back("UNKNOWN FLAG");//error

  return flags;
  //return combine(flags,std::string("|"));
}

std::vector<std::string> get_mem_region_flags( __u16 flag )
{
  std::vector<std::string> flags;
  if(flag & JAILHOUSE_MEM_READ)
    flags.push_back("JAILHOUSE_MEM_READ");
  if ( flag & JAILHOUSE_MEM_WRITE )
      flags.push_back("JAILHOUSE_MEM_WRITE");
  if ( flag & JAILHOUSE_MEM_EXECUTE )
      flags.push_back("JAILHOUSE_MEM_EXECUTE");
  if ( flag & JAILHOUSE_MEM_DMA )
      flags.push_back("JAILHOUSE_MEM_DMA");
  if ( flag & JAILHOUSE_MEM_IO )
      flags.push_back("JAILHOUSE_MEM_IO");
  if ( flag & JAILHOUSE_MEM_COMM_REGION )
      flags.push_back("JAILHOUSE_MEM_COMM_REGION");
  if ( flag & JAILHOUSE_MEM_LOADABLE )
      flags.push_back("JAILHOUSE_MEM_LOADABLE");
  if ( flag &JAILHOUSE_MEM_ROOTSHARED )
      flags.push_back("JAILHOUSE_MEM_ROOTSHARED");
  if ( flag & JAILHOUSE_MEM_IO_UNALIGNED )
      flags.push_back("JAILHOUSE_MEM_IO_UNALIGNED");
  if ( flag & JAILHOUSE_MEM_IO_8)
      flags.push_back("JAILHOUSE_MEM_IO_8");
  if ( flag & JAILHOUSE_MEM_IO_16)
      flags.push_back("JAILHOUSE_MEM_IO_16");
  if ( flag & JAILHOUSE_MEM_IO_32)
      flags.push_back("JAILHOUSE_MEM_IO_32");
  if ( flag & JAILHOUSE_MEM_IO_64)
      flags.push_back("JAILHOUSE_MEM_IO_64");
 //  return combine(flags,std::string("|"));
  return flags;
}

std::vector<std::string> get_cell_desc_flags( __u64 flag)
{
  std::vector<std::string> flags;
  if( flag & JAILHOUSE_CELL_PASSIVE_COMMREG )
    flags.push_back("JAILHOUSE_CELL_PASSIVE_COMMREG");
  if( flag & JAILHOUSE_CELL_DEBUG_CONSOLE )
    flags.push_back("JAILHOUSE_CELL_DEBUG_CONSOLE");
  return flags;
}


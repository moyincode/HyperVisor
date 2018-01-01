#ifndef non_root_config_H
#define non_root_config_H

namespace non_root
{
  char * header = " /*\n"
    " * Jailhouse, a Linux-based partitioning hypervisor\n"
    " *\n"
    " * Configuration for linux-demo inmate on Jetson TX1:\n"
    " * 2 CPUs, 428M RAM, serial port D\n"
    " *\n"
    " * Copyright (c) OTH Regensburg, 2017\n"
    " *\n"
    " * Authors:\n"
    " *  Ralf Ramsauer <ralf.ramsauer@oth-regensburg.de>\n"
    " *\n"
    " * This work is licensed under the terms of the GNU GPL, version 2.  See\n"
    " * the COPYING file in the top-level directory.\n"
    " *\n"
    " * Note: the root Linux should be started with \"mem=3584M\"\n"
    " */\n"
    "\n"
    "#include <jailhouse/types.h>\n"
    "#include <jailhouse/cell-config.h>\n"
    "\n"
    "#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])\n"
    "\n"
    "#ifndef CONFIG_INMATE_BASE\n"
    "#define CONFIG_INMATE_BASE 0x0\n"
    "#endif\n"
    "\n";

  char * struct_heading =  "struct {\n"
    "	struct jailhouse_cell_desc cell;\n"
    "	__u64 cpus[1];\n"																			
    "	struct jailhouse_memory mem_regions[%s];\n"						// number of mem_regions
    "	struct jailhouse_irqchip irqchips[%s];\n"							// number of irqchips
    "	struct jailhouse_pci_device pci_devices[%s];\n"				// number of pci_device
    "} __attribute__((packed)) config = {\n";

  char * cell_body = ".cell = {\n"
    "		.signature = %s,\n"
    "		.revision = %s,\n"
    "		.name = \"%s\",\n"								// cell name
    "		.flags = %s,\n"				// shr check if the flages will change
    "\n"
    "		.cpu_set_size = sizeof(config.cpus),\n"
    "		.num_memory_regions = ARRAY_SIZE(config.mem_regions),\n"
    "		.num_irqchips = ARRAY_SIZE(config.irqchips),\n"
    "		.num_pci_devices = ARRAY_SIZE(config.pci_devices),\n"
    "\n"
    "		.vpci_irq_base = %s,\n"														// shr check irq_base
    "\n"
    "		.cpu_reset_address = CONFIG_INMATE_BASE,\n"
    "	},\n"
    "\n"
    "	.cpus = {\n"
    "		%s,\n"																					// cpu in hex
    "	},\n"
    "\n";
}
namespace root
{
  char * header = "/*\n"
    " * Jailhouse Jetson TX1 support\n"
    " *\n"
    " * Copyright (C) 2016 Evidence Srl\n"
    " *\n"
    " * Authors:\n"
    " *  Claudio Scordino <claudio@evidence.eu.com>\n"
    " *  Bruno Morelli <b.morelli@evidence.eu.com>\n"
    " *\n"
    " * This work is licensed under the terms of the GNU GPL, version 2.  See\n"
    " * the COPYING file in the top-level directory.\n"
    " *\n"
    " * NOTE: Add \"mem=3968M vmalloc=512M\" to the kernel command line.\n"
    " */\n"
    "\n"
    "#include <jailhouse/types.h>\n"
    "#include <jailhouse/cell-config.h>\n"
    "\n"
    "#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))\n"
    "\n";

  char * struct_heading = "struct {\n"
    "  struct jailhouse_system header;\n"
    "  __u64 cpus[1];\n"
    "  struct jailhouse_memory mem_regions[%s];\n"
    "  struct jailhouse_irqchip irqchips[%s];\n"
    "  struct jailhouse_pci_device pci_devices[%s];\n"
    "} __attribute__((packed)) config = {\n";

  char * root_header = "  .header = {\n"
    "    .signature = %s,\n"
    "    .revision = %s,\n"
    "    .hypervisor_memory = {\n"
    "      .phys_start = %s,\n"
    "      .size = %s,\n"
    "    },\n";

  char * root_debug_console ="    .debug_console = {\n"
    "      .address = %s,\n"
    "      .size = %s,\n"
    "      .flags = %s,\n"
    "    },\n";
  char * root_paltform_info ="    .platform_info = {\n"
    "      .pci_mmconfig_base = %s,\n"
    "      .pci_mmconfig_end_bus = %s,\n"
    "      .pci_is_virtual = %s,\n"
    "\n"
    "      .arm = {\n"
    //"        .gic_version = %s,\n"
    "        .gicd_base = %s,\n"
    "        .gicc_base = %s,\n"
    "        .gich_base = %s,\n"
    "        .gicv_base = %s,\n"
    "        .maintenance_irq = %s,\n"
    "      }\n"
    "    },\n";

  char * root_cell ="    .root_cell = {\n"
    "      .name = \"%s\",\n"
    "      .cpu_set_size = sizeof(config.cpus),\n"
    "      .num_memory_regions = ARRAY_SIZE(config.mem_regions),\n"
    "      .num_irqchips = ARRAY_SIZE(config.irqchips),\n"
    "      .num_pci_devices = ARRAY_SIZE(config.pci_devices),\n"
    "\n"
    "      .vpci_irq_base = %s,\n"
    "    },\n"
    "  },\n"
    "\n"
    "  .cpus = {\n"
    "    %s,\n"   // cpu to hex
    "  },\n"
    "\n"
    "\n";

}
  char * mem_start = "	.mem_regions = {\n";

  char * mem_body = "		/* %s */ {\n"									// name
    "			.phys_start = %s,\n"									// phys_start
    "			.virt_start = %s,\n"									//virt_start
    "			.size = %s,\n"														// size
    "			.flags = %s,\n"		// flags
    "		},\n";

  char * mem_end = "	},\n"
    "\n";

  char * irq_start = "	.irqchips = {\n";

  char * irq_body = "		/* %s */ {\n"									// name
    "			.address = %s,\n"											//address
    "			.pin_base = %s,\n"														//pinbase
    "			.pin_bitmap = {\n"														// shr check pin_bitmap
    "				%s\n"
    "			},\n"
    "		},\n";

  char * irq_end = "	},\n"
    "\n";

  char * pci_start = "	.pci_devices = {\n";

  char * pci_body = "		/* 00:00.0 */ {\n"								 //shr check name
    "			.type = %s,\n"																		// type
    "			.bdf = %s,\n"																	// bdf
    "			.bar_mask = {\n"
    "				%s,\n"																				// bar_mask
    "			},\n"
    "			.shmem_region = %s,\n"																//shmem_region
    "			.shmem_protocol = %s,\n"    // sheme_protocol
    "		},\n";

  char * pci_end = "	},\n";

  char * file_end = "};\n";



#endif

/*
 * Jailhouse Jetson TX1 support
 *
 * Copyright (C) 2016 Evidence Srl
 *
 * Authors:
 *  Claudio Scordino <claudio@evidence.eu.com>
 *  Bruno Morelli <b.morelli@evidence.eu.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 *
 * NOTE: Add "mem=3968M vmalloc=512M" to the kernel command line.
 */

#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

struct {
  struct jailhouse_system header;
  __u64 cpus[1];
  struct jailhouse_memory mem_regions[19];
  struct jailhouse_irqchip irqchips[2];
  struct jailhouse_pci_device pci_devices[1];
} __attribute__((packed)) config = {
  .header = {
    .signature = JHSYST,
    .revision = JAILHOUSE_CONFIG_REVISION,
    .hypervisor_memory = {
      .phys_start = 0xfc000000,
      .size = 0x3f00000,
    },
    .debug_console = {
      .address = 0x70006300,
      .size = 0x40,
      .flags = JAILHOUSE_CON1_TYPE_8250|JAILHOUSE_CON1_ACCESS_MMIO|JAILHOUSE_CON1_REGDIST_4|JAILHOUSE_CON2_TYPE_ROOTPAGE,
    },
    .platform_info = {
      .pci_mmconfig_base = 0x48000000,
      .pci_mmconfig_end_bus = 0,
      .pci_is_virtual = 1,

      .arm = {
        .gicd_base = 0x50041000,
        .gicc_base = 0x50042000,
        .gich_base = 0x50044000,
        .gicv_base = 0x50046000,
        .maintenance_irq = 25,
      }
    },
    .root_cell = {
      .name = "Jetson-TK1",
      .cpu_set_size = sizeof(config.cpus),
      .num_memory_regions = ARRAY_SIZE(config.mem_regions),
      .num_irqchips = ARRAY_SIZE(config.irqchips),
      .num_pci_devices = ARRAY_SIZE(config.pci_devices),

      .vpci_irq_base = 148,
    },
  },

  .cpus = {
    0x10,
  },


	.mem_regions = {
		/* Jetson-TK1memregion0 */ {
			.phys_start = 0x1000000,
			.virt_start = 0x1000000,
			.size = 0x3f000000,
			.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO,
		},
		/* Jetson-TK1memregion1 */ {
			.phys_start = 0x50000000,
			.virt_start = 0x50000000,
			.size = 0x4000,
			.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO,
		},
		/* Jetson-TK1memregion2 */ {
			.phys_start = 0x54200000,
			.virt_start = 0x54200000,
			.size = 0x4000,
			.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO,
		},
		/* Jetson-TK1memregion3 */ {
			.phys_start = 0x54240000,
			.virt_start = 0x54240000,
			.size = 0x4000,
			.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO,
		},
		/* Jetson-TK1memregion4 */ {
			.phys_start = 0x54280000,
			.virt_start = 0x54280000,
			.size = 0x4000,
			.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO,
		},
		/* Jetson-TK1memregion5 */ {
			.phys_start = 0x57000000,
			.virt_start = 0x57000000,
			.size = 0x2000000,
			.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO,
		},
		/* Jetson-TK1memregion6 */ {
			.phys_start = 0x60002000,
			.virt_start = 0x60002000,
			.size = 0x5000,
			.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO,
		},
		/* Jetson-TK1memregion7 */ {
			.phys_start = 0x6000d000,
			.virt_start = 0x6000d000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO,
		},
		/* Jetson-TK1memregion8 */ {
			.phys_start = 0x70000800,
			.virt_start = 0x70000800,
			.size = 0x100,
			.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO,
		},
		/* Jetson-TK1memregion9 */ {
			.phys_start = 0x70006000,
			.virt_start = 0x70006000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO,
		},
		/* Jetson-TK1memregion10 */ {
			.phys_start = 0x7000c000,
			.virt_start = 0x7000c000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO,
		},
		/* Jetson-TK1memregion11 */ {
			.phys_start = 0x7000d000,
			.virt_start = 0x7000d000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO,
		},
		/* Jetson-TK1memregion12 */ {
			.phys_start = 0x7000e000,
			.virt_start = 0x7000e000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO,
		},
		/* Jetson-TK1memregion13 */ {
			.phys_start = 0x70019000,
			.virt_start = 0x70019000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO,
		},
		/* Jetson-TK1memregion14 */ {
			.phys_start = 0x70090000,
			.virt_start = 0x70090000,
			.size = 0xa000,
			.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO,
		},
		/* Jetson-TK1memregion15 */ {
			.phys_start = 0x700b0000,
			.virt_start = 0x700b0000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO,
		},
		/* Jetson-TK1memregion16 */ {
			.phys_start = 0x70110000,
			.virt_start = 0x70110000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO,
		},
		/* Jetson-TK1memregion17 */ {
			.phys_start = 0x7d004000,
			.virt_start = 0x7d004000,
			.size = 0x8000,
			.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO,
		},
		/* Jetson-TK1memregion18 */ {
			.phys_start = 0x80000000,
			.virt_start = 0x80000000,
			.size = 0x7c000000,
			.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_EXECUTE,
		},
	},

	.irqchips = {
		/* Jetson-TK1irqchip0 */ {
			.address = 0x50041000,
			.pin_base = 32,
			.pin_bitmap = {
				0xffffffff,0xffffffff,0xffffffff,0xffffffff
			},
		},
		/* Jetson-TK1irqchip1 */ {
			.address = 0x50041000,
			.pin_base = 160,
			.pin_bitmap = {
				0xffffffff,0x0,0x0,0x0
			},
		},
	},

	.pci_devices = {
		/* 00:00.0 */ {
			.type = JAILHOUSE_PCI_TYPE_IVSHMEM,
			.bdf = 0x0,
			.bar_mask = {
				0xffffff00,0xffffffff,0x0,0x0,0x0,0x0,
			},
			.shmem_region = 19,
			.shmem_protocol = JAILHOUSE_SHMEM_PROTO_VETH,
		},
	},
};

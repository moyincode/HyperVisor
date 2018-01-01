 /*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Configuration for linux-demo inmate on Jetson TX1:
 * 2 CPUs, 428M RAM, serial port D
 *
 * Copyright (c) OTH Regensburg, 2017
 *
 * Authors:
 *  Ralf Ramsauer <ralf.ramsauer@oth-regensburg.de>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 *
 * Note: the root Linux should be started with "mem=3584M"
 */

#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

#ifndef CONFIG_INMATE_BASE
#define CONFIG_INMATE_BASE 0x0
#endif

struct {
	struct jailhouse_cell_desc cell;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[4];
	struct jailhouse_irqchip irqchips[2];
	struct jailhouse_pci_device pci_devices[1];
} __attribute__((packed)) config = {
.cell = {
		.signature = JHCELL,
		.revision = JAILHOUSE_CONFIG_REVISION,
		.name = "jetson-tx1-linux-demo",
		.flags = JAILHOUSE_CELL_PASSIVE_COMMREG|JAILHOUSE_CELL_DEBUG_CONSOLE,

		.cpu_set_size = sizeof(config.cpus),
		.num_memory_regions = ARRAY_SIZE(config.mem_regions),
		.num_irqchips = ARRAY_SIZE(config.irqchips),
		.num_pci_devices = ARRAY_SIZE(config.pci_devices),

		.vpci_irq_base = 152,

		.cpu_reset_address = CONFIG_INMATE_BASE,
	},

	.cpus = {
		0xc,
	},

	.mem_regions = {
		/* jetson-tx1-linux-demomemregion0 */ {
			.phys_start = 0x70006000,
			.virt_start = 0x70006000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_IO|JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE,
		},
		/* jetson-tx1-linux-demomemregion2 */ {
			.phys_start = 0x161200000,
			.virt_start = 0xe8000000,
			.size = 0x1acf0000,
			.flags = JAILHOUSE_MEM_EXECUTE|JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE,
		},
		/* jetson-tx1-linux-demomemregion1 */ {
			.phys_start = 0x17bef0000,
			.virt_start = 0x0,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_EXECUTE|JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE,
		},
		/* jetson-tx1-linux-demomemregion3 */ {
			.phys_start = 0x17bf00000,
			.virt_start = 0x17bf00000,
			.size = 0x100000,
			.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE,
		},
	},

	.irqchips = {
		/* jetson-tx1-linux-demoirqchip1 */ {
			.address = 0x2fb90a8,
			.pin_base = 0,
			.pin_bitmap = {
				0x1000000,0x0,0x0,0x0
			},
		},
		/* jetson-tx1-linux-demoirqchip0 */ {
			.address = 0x2fb90a8,
			.pin_base = 20,
			.pin_bitmap = {
				0x0,0x10,0x0,0x0
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
			.shmem_region = 3,
			.shmem_protocol = JAILHOUSE_SHMEM_PROTO_VETH,
		},
	},
};

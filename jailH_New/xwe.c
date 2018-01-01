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
	struct jailhouse_memory mem_regions[1];
	struct jailhouse_irqchip irqchips[1];
	struct jailhouse_pci_device pci_devices[1];
} __attribute__((packed)) config = {
.cell = {
		.signature = erewr,
		.revision = werwer,
		.name = "xwe",
		.flags = JAILHOUSE_CELL_PASSIVE_COMMREG|JAILHOUSE_CELL_DEBUG_CONSOLE,

		.cpu_set_size = sizeof(config.cpus),
		.num_memory_regions = ARRAY_SIZE(config.mem_regions),
		.num_irqchips = ARRAY_SIZE(config.irqchips),
		.num_pci_devices = ARRAY_SIZE(config.pci_devices),

		.vpci_irq_base = 0,

		.cpu_reset_address = CONFIG_INMATE_BASE,
	},

	.cpus = {
		0xc,
	},

	.mem_regions = {
		/* asf */ {
			.phys_start = 0xa,
			.virt_start = 0xa,
			.size = 0x2,
			.flags = JAILHOUSE_MEM_EXECUTE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE,
		},
	},

	.irqchips = {
		/* sdd */ {
			.address = 0x3e8,
			.pin_base = 1,
			.pin_bitmap = {
				0x19
			},
		},
	},

	.pci_devices = {
		/* 00:00.0 */ {
			.type = bdf,
			.bdf = 0x19,
			.bar_mask = {
				0x2,0x2,
			},
			.shmem_region = 25,
			.shmem_protocol = jfgj,
		},
	},
};

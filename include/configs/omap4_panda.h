/*
 * (C) Copyright 2010
 * Texas Instruments Incorporated.
 * Steve Sakoman  <steve@sakoman.com>
 *
 * Configuration settings for the TI OMAP4 Panda board.
 * See ti_omap4_common.h for OMAP4 common part
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_PANDA_H
#define __CONFIG_PANDA_H

/*
 * High Level Configuration Options
 */

/* USB UHH support options */
#define CONFIG_CMD_USB
#define CONFIG_USB_HOST
#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_OMAP
#define CONFIG_USB_STORAGE
#define CONFIG_SYS_USB_EHCI_MAX_ROOT_PORTS 3

#define CONFIG_OMAP_EHCI_PHY1_RESET_GPIO 1
#define CONFIG_OMAP_EHCI_PHY2_RESET_GPIO 62

/* USB Networking options */
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_SMSC95XX

#define CONFIG_UBOOT_ENABLE_PADS_ALL

#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP

#include <configs/ti_omap4_common.h>
#define CONFIG_CMD_NET

/* GPIO */
#define CONFIG_CMD_GPIO

/* ENV related config options */
#define CONFIG_ENV_IS_NOWHERE

#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG

/*****************************************************************************
 * FreeBSD customizations from here down.
 ****************************************************************************/

#define CONFIG_SYS_DCACHE_OFF

/* Add the API and ELF features needed for ubldr. */
#ifndef CONFIG_SPL_BUILD
#define CONFIG_API
#define CONFIG_CMD_ELF
#define CONFIG_CMD_ENV_EXISTS
#define CONFIG_EFI_PARTITION
#define CONFIG_SYS_MMC_MAX_DEVICE 2
#ifndef CONFIG_SYS_DCACHE_OFF
#define CONFIG_CMD_CACHE
#endif
#endif

/* Save the env to the fat partition. */
#ifndef CONFIG_SPL_BUILD
#undef  CONFIG_ENV_IS_NOWHERE
#undef  CONFIG_ENV_IS_IN_NAND
#undef  CONFIG_ENV_IS_IN_MMC
#define CONFIG_ENV_IS_IN_FAT
#define CONFIG_FAT_WRITE
#define FAT_ENV_INTERFACE      "mmc"
#define FAT_ENV_DEVICE_AND_PART        "0"
#define FAT_ENV_FILE           "u-boot.env"
#endif

/* Create a small(ish) boot environment for FreeBSD. */
#ifndef CONFIG_SPL_BUILD
#undef  CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_EXTRA_ENV_SETTINGS \
	"loadaddr=88000000\0" \
	"Fatboot=" \
	  "env exists loaderdev || env set loaderdev ${fatdev}; " \
	  "env exists UserFatboot && run UserFatboot; " \
	  "echo Booting from: ${fatdev} ${bootfile}; " \
	  "fatload ${fatdev} ${loadaddr} ${bootfile} && bootelf; " \
	"\0" \
	"Netboot=" \
	  "env exists loaderdev || env set loaderdev net; " \
	  "env exists UserNetboot && run UserNetboot; " \
	  "dhcp ${loadaddr} ${bootfile} && bootelf; " \
	"\0" \
	"Preboot=" \
	  "env exists bootfile || bootfile=ubldr; " \
	  "env exists uenv_file || uenv_file=uEnv.txt; " \
	  "env exists SetupFdtfile && run SetupFdtfile; " \
	  "env exists SetupFatdev && run SetupFatdev; " \
	  "env exists SetupUenv && run SetupUenv; " \
	  "env exists UserPreboot && run UserPreboot; " \
	"\0" \
	"SetupFdtfile=" \
	  "env exists fdt_file || env set fdt_file omap4-panda.dtb; " \
	"\0" \
	"SetupFatdev=" \
	  "env exists fatdev || fatdev='mmc 0'; " \
	"\0" \
	"SetupUenv=" \
	  "fatload ${fatdev} ${loadaddr} ${uenv_file} && " \
	    "env import -t ${loadaddr} ${filesize}; " \
	"\0"

#undef  CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND     "run Fatboot"
#undef  CONFIG_PREBOOT
#define CONFIG_PREBOOT         "run Preboot"
#endif

#endif /* __CONFIG_PANDA_H */

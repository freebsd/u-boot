/*
 * (C) Copyright: 2013
 * Gumstix, Inc - http://www.gumstix.com
 * Maintainer: Ash Charles  <ash@gumstix.com>
 *
 * Configuration settings for the Gumstix DuoVero board.
 * See omap4_common.h for OMAP4 common part
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __CONFIG_DUOVERO_H
#define __CONFIG_DUOVERO_H

/*
 * High Level Configuration Options
 */
#define CONFIG_DUOVERO
#define MACH_TYPE_OMAP4_DUOVERO              4097    /* Until the next sync */
#define CONFIG_MACH_TYPE                MACH_TYPE_OMAP4_DUOVERO

#include <configs/ti_omap4_common.h>

#undef CONFIG_SPL_OS_BOOT
#undef CONFIG_EFI_PARTITION

#undef CONFIG_SYS_EMIF_PRECALCULATED_TIMING_REGS
#define CONFIG_SYS_AUTOMATIC_SDRAM_DETECTION
#define CONFIG_SYS_DEFAULT_LPDDR2_TIMINGS

/* USB UHH support options */
#define CONFIG_USB_HOST
#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_OMAP
#define CONFIG_USB_STORAGE
#define CONFIG_SYS_USB_EHCI_MAX_ROOT_PORTS 3

#define CONFIG_OMAP_EHCI_PHY1_RESET_GPIO 1
#define CONFIG_OMAP_EHCI_PHY2_RESET_GPIO 62

#define CONFIG_SYS_ENABLE_PADS_ALL

#define CONFIG_SMC911X
#define CONFIG_SMC911X_32_BIT
#define CONFIG_SMC911X_BASE		0x2C000000

/* GPIO */

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
	  "env exists fdt_file || env set fdt_file omap4-duovero-parlor.dtb; " \
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

#endif /* __CONFIG_DUOVERO_H */

#
# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# BoardConfig.mk
#
# Product-specific compile-time definitions.
#

# Set this up here so that BoardVendorConfig.mk can override it
BOARD_USES_GENERIC_AUDIO := false

BOARD_USES_LIBSECRIL_STUB := true

# Use the non-open-source parts, if they're present
-include vendor/samsung/vzwtabmtd/BoardConfigVendor.mk

# Vold
BOARD_VOLD_EMMC_SHARES_DEV_MAJOR := true

# USB
BOARD_USE_USB_MASS_STORAGE_SWITCH := true

# ARMv7-A Cortex-A8 architecture
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi
TARGET_ARCH_VARIANT := armv7-a-neon
ARCH_ARM_HAVE_TLS_REGISTER := true
TARGET_GLOBAL_CFLAGS += -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp
TARGET_GLOBAL_CPPFLAGS += -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp
ARCH_ARM_HAVE_TLS_REGISTER := true
#ANDROID_ARM_LINKER := true

TARGET_NO_BOOTLOADER := true
#TARGET_NO_RECOVERY := true
#TARKET_NO_KERNEL := true
TARGET_NO_RADIOIMAGE := true

TARGET_BOARD := SCH-I800
#TARGET_PROVIDES_INIT := true
#TARGET_PROVIDES_INIT_TARGET_RC := true
TARGET_BOARD_PLATFORM := s5pc110
TARGET_BOARD_PLATFORM_GPU := POWERVR_SGX540_120
TARGET_BOOTLOADER_BOARD_NAME := galaxytab
TARGET_RECOVERY_INITRC := device/samsung/aries-common/recovery.rc
BOARD_PROVIDES_BOOTMODE := true
#BOARD_HAS_JANKY_BACKBUFFER := true

# Bluetooth
BOARD_HAVE_BLUETOOTH := true
BOARD_HAVE_BLUETOOTH_BCM := true

# WiFi related defines
WPA_SUPPLICANT_VERSION := VER_0_6_X
BOARD_WPA_SUPPLICANT_DRIVER := WEXT
BOARD_WLAN_DEVICE := bcm4329
WIFI_DRIVER_MODULE_PATH := "/lib/modules/dhd.ko"
WIFI_DRIVER_MODULE_NAME := "dhd"
WIFI_DRIVER_FW_STA_PATH := "/system/etc/wifi/bcm4329_sta.bin"
WIFI_DRIVER_FW_AP_PATH := "/system/etc/wifi/bcm4329_aps.bin"
WIFI_DRIVER_MODULE_ARG := "firmware_path=/system/etc/wifi/bcm4329_sta.bin nvram_path=/system/etc/wifi/nvram_net.txt dhd_watchdog_ms=10 dhd_poll=1"
WIFI_IFACE_DIR := "/data/misc/wifi"
CONFIG_DRIVER_WEXT := true
BOARD_WEXT_NO_COMBO_SCAN := true

USE_CAMERA_STUB := false
ifeq ($(USE_CAMERA_STUB),false)
BOARD_CAMERA_LIBRARIES := libcamera
endif
BOARD_V4L2_DEVICE := /dev/video1
BOARD_CAMERA_DEVICE := /dev/video0
BOARD_SECOND_CAMERA_DEVICE := /dev/video2

# OpenGL stuff
BOARD_EGL_CFG := vendor/samsung/common/SCH-I800/proprietary/egl/egl.cfg
TARGET_BOARD_PLATFORM_GPU := POWERVR_SGX540_120

# Device related defines
BOARD_KERNEL_CMDLINE := console=ttyFIQ0,115200 init=/init no_console_suspend
BOARD_KERNEL_BASE := 0x02e00000
TARGET_PREBUILT_KERNEL := device/samsung/vzwtabmtd/kernel

BOARD_BOOTIMAGE_PARTITION_SIZE := 7864320
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 196608000
BOARD_USERDATAIMAGE_PARTITION_SIZE := 2013265920
# The size of a block that can be marked bad.
BOARD_FLASH_BLOCK_SIZE := 4096

# Vold
BOARD_VOLD_EMMC_SHARES_DEV_MAJOR := true

# Recovery
TARGET_USERIMAGES_USE_EXT4 := true
BOARD_HAS_NO_SELECT_BUTTON := true
BOARD_HAS_NO_RECOVERY_PARTITION := true
BOARD_HAS_NO_MISC_PARTITION := true
BOARD_HAS_DOWNLOAD_MODE := true
BOARD_USES_BML_OVER_MTD := true
BOARD_CUSTOM_BOOTIMG_MK := device/samsung/aries-common/shbootimg.mk
TARGET_RECOVERY_PRE_COMMAND := "echo 1 > /cache/.startrecovery; sync;"

# Include aries specific stuff
-include device/samsung/aries-common/Android.mk

TARGET_OTA_ASSERT_DEVICE := aries,vzwtab,vzwtabmtd,galaxytab,SCH-I800


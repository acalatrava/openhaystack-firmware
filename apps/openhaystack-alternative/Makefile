PROJECT_NAME = $(shell basename "$(realpath ./)")

APPLICATION_SRCS = $(notdir $(wildcard ./*.c))
APPLICATION_SRCS += softdevice_handler.c
APPLICATION_SRCS += app_util_platform.c
APPLICATION_SRCS += nrf_drv_common.c
APPLICATION_SRCS += nrf_delay.c
APPLICATION_SRCS += app_error.c
APPLICATION_SRCS += app_error_weak.c

USE_NRF52 := $(filter nrf52,$(MAKECMDGOALS))

SDK_VERSION = 11

# BOARD_E104BT5032A is for E104-BT5032A board https://www.aliexpress.com/item/4000538644215.html
# BOARD_CUSTOM is for this "AliExpress beacon" https://www.aliexpress.com/item/32826502025.html

# Compile for nrf52 by default, use "NRF_MODEL=nrf51 make" to compile for nrf51 platform
ifeq ($(NRF_MODEL), nrf51)
SOFTDEVICE_MODEL = s130
BOARD ?= BOARD_CUSTOM
else
SOFTDEVICE_MODEL = s132
BOARD ?= BOARD_E104BT5032A
NRF_MODEL = nrf52
endif

default: all

# I had some troubles to flashing the E104-BT5032A module, still not sure why, but I created this script that at least works better 
# to me than "make flash". It works by trying to recover the device on a loop which it will erase all the flash contents and then 
# it will programming it. You may need to unplug and plug VCC while executing this loop
e104install:
	mergehex -m ../../nrf5x-base/sdk/nrf51_sdk_11.0.0/components/softdevice/s132/hex/s132_nrf52_2.0.0_softdevice.hex _build/*.hex -o _build/full_firmware.bin
	nrfjprog -f nrf52 --recover; while [ "$$?" -ne "0" ]; do echo "****** IMPORTANT: If you see this message for too long, please try to disconnect and connect VCC ******" && nrfjprog -f nrf52 --recover; done
	nrfjprog -f nrf52 --program _build/full_firmware.bin --reset

LIBRARY_PATHS += .
#SOURCE_PATHS += .

NRF_BASE_PATH ?= ../../nrf5x-base
include $(NRF_BASE_PATH)/make/Makefile
PROJECT = blink
BUILD_DIR = bin

CFILES = blink.c

#DEVICE?=samr34j18
DEVICE?=samd10d14

OPENCM3_DIR=libopencm3
include $(OPENCM3_DIR)/mk/genlink-config.mk
include rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk

tags:
	ctags -R .

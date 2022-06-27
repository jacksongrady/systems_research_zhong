TARGET = memwrite
SRCS = memwrite.c

LINKER_SCRIPT = ../../flash/STM32F411VE_FLASH.ld

# Generate debug info
DEBUG = 1

# Choose processor
CDEFS  = -DSTM32F411xe
# Enable FPU
#CDEFS += -D__VFP_FP__

include ../armf4.mk
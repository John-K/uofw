# Copyright (C) 2021 The uOFW team
# See the file COPYING for copying permission.

TARGET = lowio
OBJS = lowio.o gpio_driver.o sysreg_driver.o

DEBUG = 0
INSTALLER = 1

# TODO make list accurate
LIBS = -lSysMemForKernel -lsceSuspendForKernel -lKDebugForKernel -lLoadCoreForKernel -lInterruptManagerForKernel -lSysclibForKernel -lThreadManForKernel -lIoFileMgrForKernel -lModuleMgrForKernel -lInitForKernel -lUtilsForKernel

include ../../lib/build.mak



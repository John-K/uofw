/* Copyright (C) 2021 The uOFW team    
   See the file COPYING for copying permission.
*/

/* Add note about provenance of lowio */

#include <common_imp.h>
#include "gpio_driver.h"
#include <sysmem_sysevent.h>

SCE_MODULE_INFO("sceLowIO_Driver", SCE_MODULE_KERNEL | SCE_MODULE_ATTR_CANT_STOP | SCE_MODULE_ATTR_EXCLUSIVE_LOAD | 
                                  SCE_MODULE_ATTR_EXCLUSIVE_START, 1, 2);
SCE_MODULE_BOOTSTART("_sceLowioModuleStart");
SCE_SDK_VERSION(SDK_VERSION);

s32 lowio_init()
{
    sceKernelUnregisterSysEventHandler(NULL);
    //sceSysregIntrInit();
    //sceSysregPllUpdateFrequency();
    sceKernelRegisterSysEventHandler(NULL);
    return 0;
}

s32 _sceLowioModuleStart(SceSize argSize __attribute__((unused)), const void *argBlock __attribute__((unused)))
{
    lowio_init();
    _sceGpioInit(argSize, argBlock);
    /*
    FUN_00003bfc(argSize,argBlock);
    FUN_00004b50(argSize,argBlock);
    FUN_00005234(argSize,argBlock);
    FUN_0000887c(argSize,argBlock);
    FUN_00009814(argSize,argBlock);
    FUN_0000b014(argSize,argBlock);
    */
    return 0;
}
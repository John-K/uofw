/* Copyright (C) 2021 The uOFW team
   See the file COPYING for copying permission.
*/

#include <common_imp.h>
#include <interruptman.h>

#define GPIO_GLOBAL_CONTEXT_BASE 0x220

typedef struct {
    u32 unk[4];           // 0x220
    u32 intr_enabled;     // 0x230
    u32 unk2;
    u32 timerCapture_enabled; // 0x238
    u32 unk3;
    u32 intr_always_on;   // 0x240
} GlobalGpioCtx;

static GlobalGpioCtx *gpioCtx = (void *)GPIO_GLOBAL_CONTEXT_BASE;

// FUN_000031b8 and FUN_00002cfc
s32 _sceGpioInit(SceSize argSize __attribute__((unused)), const void *argBlock __attribute__((unused)))
{
    //TODO: RE FUN_00002cfc
    return 0;
}

int sceGpioAcquireIntr(u32 intrNum)
{
    if (intrNum >= 0x20)
        return SCE_ERROR_INVALID_INDEX;

    s32 intrState = sceKernelCpuSuspendIntr();
    u32 status = 1 & (HW(HW_GPIO_INTERRUPT_STATUS) >> intrNum);
    HW(HW_GPIO_INTERRUPT_STATUS) = status << intrNum;
    sceKernelCpuResumeIntrWithSync(intrState);

    return (int)status;
}

int sceGpioDisableIntr(u32 intrNum)
{
    u32 ret;

    if (intrNum >= 0x20)
        return SCE_ERROR_INVALID_INDEX;

    s32 intrState = sceKernelCpuSuspendIntr();
    u32 newValue = gpioCtx->intr_enabled & ~(1 << intrNum);
    HW(HW_GPIO_INTERRUPT_ENABLE) &= newValue | gpioCtx->intr_always_on;
    ret = 1 & (gpioCtx->intr_enabled >> intrNum);
    gpioCtx->intr_enabled = newValue;
    sceKernelCpuResumeIntr(intrState);

    return ret;
}

int sceGpioEnableIntr(u32 intrNum)
{
    u32 ret;

    if (intrNum >= 0x20)
        return SCE_ERROR_INVALID_INDEX;

    s32 intrState = sceKernelCpuSuspendIntr();
    u32 newValue = gpioCtx->intr_enabled | (1 << intrNum);
    HW(HW_GPIO_INTERRUPT_ENABLE) &= gpioCtx->intr_always_on | newValue;
    ret = 1 & (gpioCtx->intr_enabled >> intrNum);
    gpioCtx->intr_enabled = newValue;
    sceKernelCpuResumeIntr(intrState);

    return ret;
}

int sceGpioDisableTimerCapture(u32 timerIndex)
{
    u32 ret;

    if (timerIndex > 3)
        return SCE_ERROR_INVALID_INDEX;

    s32 intrState = sceKernelCpuSuspendIntr();
    HW(HW_GPIO_TIMER_CAPTURE) = gpioCtx->timerCapture_enabled & ~(1 << timerIndex);
    ret = 1 & (gpioCtx->timerCapture_enabled >> timerIndex);
    gpioCtx->timerCapture_enabled = HW(HW_GPIO_TIMER_CAPTURE);
    sceKernelCpuResumeIntrWithSync(intrState);

    return ret;
}


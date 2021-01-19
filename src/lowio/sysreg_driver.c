/* Copyright (C) 2011-2021 The uOFW team
   See the file COPYING for copying permission.
*/

#include <common_imp.h>

int _updateResetForBitmask(int bitmask, int enable)
{
    int oldIntr = sceKernelCpuSuspendIntr();
    int reg = HW(HW_PERIPH_RESET);
    if (enable)
        HW(HW_PERIPH_RESET) |= bitmask;
    else
        HW(HW_PERIPH_RESET) &= ~bitmask;

    sceKernelCpuResumeIntr(oldIntr);

    return (reg & bitmask) != 0;
}

/* sceSysreg_driver_47C971B2 */
int sceSysregTopResetEnable(void)
{
    return _updateResetForBitmask(1, 1);
}

/* sceSysreg_driver_655C9CFC */
int sceSysregScResetEnable(void)
{
    return _updateResetForBitmask(2, 1);
}

/* sceSysreg_driver_457FEBA9 */
int sceSysregMeResetEnable(void)
{
    return _updateResetForBitmask(4, 1);
}

/* sceSysreg_driver_48F1C4AD */
int sceSysregMeResetDisable(void)
{
    return _updateResetForBitmask(4, 0);
}

/* sceSysreg_driver_66899952 */
int sceSysregAwResetEnable(void)
{
    return _updateResetForBitmask(8, 1);
}

/* sceSysreg_driver_AEB8DBD1 */
int sceSysregAwResetDisable(void)
{
    return _updateResetForBitmask(8, 0);
}

/* sceSysreg_driver_1A27B224 */
int sceSysregVmeResetEnable(void)
{
    return _updateResetForBitmask(0x10, 1);
}

/* sceSysreg_driver_B73D3619 */
int sceSysregVmeResetDisable(void)
{
    return _updateResetForBitmask(0x10, 0);
}

/* sceSysreg_driver_0AE8E549 */
int sceSysregAvcResetEnable(void)
{
    return _updateResetForBitmask(0x20, 1);
}

/* sceSysreg_driver_55FF02E9 */
int sceSysregAvcResetDisable(void)
{
    return _updateResetForBitmask(0x20, 0);
}

/* sceSysreg_driver_30C0A141 */
int sceSysregUsbResetEnable(void)
{
    return _updateResetForBitmask(0x40, 1);
}

/* sceSysreg_driver_9306F27B */
int sceSysregUsbResetDisable(void)
{
    return _updateResetForBitmask(0x40, 0);
}

/* sceSysreg_driver_64C8E8DD */
int sceSysregAtaResetEnable(void)
{
    return _updateResetForBitmask(0x80, 1);
}

/* sceSysreg_driver_8CFD0DCA */
int sceSysregAtaResetDisable(void)
{
    return _updateResetForBitmask(0x80, 0);
}

/* sceSysreg_driver_370419AD */
int sceSysregMsifResetEnable(int index)
{
    if (index > 1)
        return SCE_ERROR_INVALID_INDEX;

    return _updateResetForBitmask(0x100 << index, 1);
}

/* sceSysreg_driver_7DD0CBEE */
int sceSysregMsifResetDisable(u32 index)
{
    if (index > 1)
        return SCE_ERROR_INVALID_INDEX;

    return _updateResetForBitmask(0x100 << index, 0);
}

/* sceSysreg_driver_C1A37B37 */
int sceSysregKirkResetEnable(void)
{
    return _updateResetForBitmask(0x400, 1);
}

/* sceSysreg_driver_2F9B03E0 */
int sceSysregKirkResetDisable(void)
{
    return _updateResetForBitmask(0x400, 0);
}

/* sceSysreg_driver_866EEB74 */
int sceSysregAtahddResetEnable(void)
{
    return _updateResetForBitmask(0x1000, 1);
}

/* sceSysreg_driver_9EB8C49E */
int sceSysregAtahddResetDisable(void)
{
    return _updateResetForBitmask(0x1000, 0);
}

/* sceSysreg_driver_4A433DC3 */
int sceSysregUsbhostResetEnable(void)
{
    return _updateResetForBitmask(0x2000, 1);
}

/* sceSysreg_driver_9B710D3C */
int sceSysregUsbhostResetDisable(void)
{
    return _updateResetForBitmask(0x2000, 0);
}

/* sceSysreg_driver_C6C75585 */
int sceSysreg_driver_C6C75585(u32 index)
{
    if (index > 1)
        return SCE_ERROR_INVALID_INDEX;

    return _updateResetForBitmask(0x4000 << index, 1);
}

/* sceSysreg_driver_0995F8F6 */
int sceSysreg_driver_0995F8F6(u32 index)
{
    if (index > 1)
        return SCE_ERROR_INVALID_INDEX;

    return _updateResetForBitmask(0x4000 << index, 0);
}

/* sceSysreg_driver_72887197 */
int sceSysreg_driver_72887197(void)
{
    return _updateResetForBitmask(1, 1);
}

/* sceSysreg_driver_32E02FDF */
int sceSysreg_driver_32E02FDF(void)
{
    return _updateResetForBitmask(1, 0);
}

/* sceSysreg_driver_73B3E52D */
int sceSysreg_driver_73B3E52D(void)
{
    return (HW(HW_PERIPH_RESET) >> 16) & 1; // is HW_RESET_UNK3 set
}

int _updateBusClockForBitmask(int bitmask, int enable)
{
    int oldIntr = sceKernelCpuSuspendIntr();
    int reg = HW(HW_BUSCLOCK_ENABLE);
    if (enable)
        HW(HW_BUSCLOCK_ENABLE) |= bitmask;
    else
        HW(HW_BUSCLOCK_ENABLE) &= ~bitmask;

    sceKernelCpuResumeIntr(oldIntr);
    return ((reg & bitmask) != 0);
}

/* sceSysreg_driver_38527743 */
int sceSysregMeBusClockEnable(void)
{
    return _updateBusClockForBitmask(1, 1);
}

/* sceSysreg_driver_C4C21CAB */
int sceSysregMeBusClockDisable(void)
{
    return _updateBusClockForBitmask(1, 0);
}

/* sceSysreg_driver_51571E8F */
int sceSysregAwRegABusClockEnable(void)
{
    return _updateBusClockForBitmask(2, 1);
}

/* sceSysreg_driver_52B74976 */
int sceSysregAwRegABusClockDisable(void)
{
    return _updateBusClockForBitmask(2, 0);
}

/* sceSysreg_driver_44277D0D */
int sceSysregAwRegBBusClockEnable(void)
{
    return _updateBusClockForBitmask(4, 1);
}

/* sceSysreg_driver_7E1B1F28 */
int sceSysregAwRegBBusClockDisable(void)
{
    return _updateBusClockForBitmask(4, 0);
}

/* sceSysreg_driver_C2E0E869 */
int sceSysregAwEdramBusClockEnable(void)
{
    return _updateBusClockForBitmask(8, 1);
}

/* sceSysreg_driver_258782A3 */
int sceSysregAwEdramBusClockDisable(void)
{
    return _updateBusClockForBitmask(8, 0);
}

// ********** HW_CLOCK_SELECT_1 related functions

int sceSysregMsifClkSelect(u32 msif_index, u32 clk_index)
{
    if (msif_index > 1)
        return SCE_ERROR_INVALID_INDEX;

    if (clk_index > 2)
        return SCE_ERROR_INVALID_VALUE;

    sceKernelCpuSuspendIntr();
    u32 index = msif_index * 2;
    u32 value = HW(HW_CLOCK_SELECT_1);
    // todo: simplify
    u32 msif_clk_sel_bits = (value >> index) & 3;
    u32 value_cleared_clk_sel_bits = value & ~(3 << index);
    u32 new_value = value_cleared_clk_sel_bits | (clk_index << index);
    HW(HW_CLOCK_SELECT_1) = new_value;
    sceKernelCpuResumeIntr();

    return msif_clk_sel_bits;
}

int sceSysregAtaClkSelect(u32 clk_index)
{
    if (clk_index > 2)
        return SCE_ERROR_INVALID_VALUE;

    sceKernelCpuSuspendIntr();
    u32 value = HW(HW_CLOCK_SELECT_1);
    u32 cur_bits = (value >> 4) & 0xF; // only needs to be & 0x3 but we're copying Sony code
    HW(HW_CLOCK_SELECT_1) = value & 0xF | clk_index << 4;
    sceKernelCpuResumeIntr();
}

int sceSysregAtahddClkSelect(u32 clk_index)
{
    if (clk_index > 2)
        return SCE_ERROR_INVALID_VALUE;

    sceKernelCpuSuspendIntr();
    u32 value = HW(HW_CLOCK_SELECT_1);
    u32 cur_bits = (value >> 8) & 0xF; // only needs to be & 0x3 but we're copying Sony code
    HW(HW_CLOCK_SELECT_1) = value & 0xFF | clk_index << 8;
    sceKernelCpuResumeIntr();
}

// sceSysreg_SOMETHING_ClkSelect
int sceSysreg_driver_C2F3061F(u32 index, u32 clk_index)
{
    if (index > 1)
        return SCE_ERROR_INVALID_INDEX;

    if (clk_index > 3)
        return SCE_ERROR_INVALID_VALUE;

    sceKernelCpuSuspendIntr();
    u32 offset = index * 2 + 10;
    u32 value = HW(HW_CLOCK_SELECT_1);
    u32 cur_bits = (value >> offset) & 0x3;
    u32 value_cleared_bits = value & ~(3 << offset);
    HW(HW_CLOCK_SELECT_1) = value_cleared_bits | (clk_index << offset);
    sceKernelCpuResumeIntr();
    return cur_bits;
}

// ********** HW_CLOCK_SELECT_2 related functions
int sceSysregAudioClkSelect(u32 index, u32 clk_index)
{
    if (index > 1)
        return SCE_ERROR_INVALID_INDEX;

    if (clk_index > 1)
        return SCE_ERROR_INVALID_VALUE;

    sceKernelCpuSuspendIntr();
    u32 offset = index + 0x10;
    u32 prev_value = HW(HW_CLOCK_SELECT_2);
    u32 cleared_bits =  prev_value & ~(1 << offset);
    HW(HW_CLOCK_SELECT_2) = cleared_bits | (clk_index << offset);
    sceKernelCpuResumeIntr();

    // return previous state
    return (prev_value >> offset) & 1;
}

int sceSysregApbTimerClkSelect(u32 index, u32 clk_index)
{
    if (index > 3)
        return SCE_ERROR_INVALID_INDEX;

    if (clk_index > 7)
        return SCE_ERROR_INVALID_VALUE;

    sceKernelCpuSuspendIntr();
    u32 offset = index << 2;
    u32 prev_value = HW(HW_CLOCK_SELECT_2);
    HW(HW_CLOCK_SELECT_2) = (prev_value & ~offset) | (clk_index << offset);
    sceKernelCpuResumeIntr();

    return 7 & (prev_value >> offset);
}
// TODO
// int sceSysregLcdcClkSelect_5DF2F52A()
// int sceSysreg_driver_0x9746F3B2(u32 param_1, u32 param_2)
// int sceSysreg_driver_0x434E8AF1(u32 param_1)
// int sceSysreg_driver_0x6596EBC3(u32 param_1, u32 param_2)
/*
{
    if (index > 3)
        return SCE_ERROR_INVALID_INDEX;

    if (clk_index > 7)
        return SCE_ERROR_INVALID_VALUE;

    sceKernelCpuSuspendIntr();
    u32 prev_value = HW(HW_CLOCK_SELECT_2);
    sceKernelCpuResumeIntr();
}
*/

// ********** HW_CLOCK_SELECT_3 related functions
int sceSysregSpiClkSelect(u32 index, u32 clk_index)
{
    if (index > 5)
        return SCE_ERROR_INVALID_INDEX;

    if (clk_index > 7)
        return SCE_ERROR_INVALID_VALUE;

    sceKernelCpuSuspendIntr();
    u32 offset = index << 2;
    u32 prev_value = HW(HW_CLOCK_SELECT_3);
    HW(HW_CLOCK_SELECT_3) = (prev_value & ~offset) | (clk_index << offset);
    sceKernelCpuResumeIntr();

    return 7 & (prev_value >> offset);
}

// ********** HW_PLL_CONFIG related functions
int sceSysregPllUpdateFrequency()
{
    // TODO: figure out PLL globals
    u32 v0_value = HW(HW_PLL_CONFIG);
    // 0x1cd4
    u32 a2_temp = 0x10000 - 0x3e48; // 0xc1b8
    u32 a1_temp = (v0_value & 0xF) << 2;
    u32 a0_temp = a1_temp + a2_temp;
    u32 v1_value = HW(a0_temp);
    HW(0x214 + (a1_temp & 0xFFFF)) = v1_value;

    return 0;
}

int sceSysregPllGetOutSelect()
{
    return 0xF & HW(HW_PLL_CONFIG);
}

int sceSysregPllSetOutSelect(u32 pll_index)
{
    if ((pll_index & 7) > 5)
        return SCE_ERROR_INVALID_VALUE;

    sceKernelCpuSuspendIntr();
    u32 prev_value = 0xF & HW(HW_PLL_CONFIG);
    HW(HW_PLL_CONFIG) = 0x80 | pll_index;
    u32 value = HW(HW_PLL_CONFIG);
    // RE more here, similar to sceSysregPllUpdateFrequency
    sceKernelCpuResumeIntr();

    return prev_value;
}

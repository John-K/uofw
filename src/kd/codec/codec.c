#include <common_imp.h>

#include "codec.h"
#include "lowio_gpio.h"
#include "lowio_i2c.h"
#include "lowio_sysreg.h"
#include "sysmem_sysevent.h"
#include "threadman_kernel.h"

typedef struct
{
    SceUID mutexId; // 0
    short shadowRegs[43]; // 4
    char flag; // 90
    char volumeOffset; // 91
    char volumeIndex; // 92
    char volumeTable; // 93
    short nineBitMask; // 94
    char outputDisabled; // 96
    char ready; // 97
} Codec;

enum CodecRegs {
    LeftInputVolume = 0,
    RightInputVolume = 1,
    LeftOut1Volume = 2,
    RightOut1Volume = 3,
    Reserved_4 = 4,
    ADC_DAC_Control = 5,
    Reserved_6 = 6,
    AudioInterface = 7,
    SampleRate = 8,
    Reserved_9 = 9,
    LeftDACVolume = 10,
    RightDACVolume = 11,
    BassControl = 12,
    TrebleControl = 13,
    Unknown_14 = 14, // missing from table in datasheet
    Reset = 15,
    SpatialControl = 16,
    AutoLevelControl_1 = 17,
    AutoLevelControl_2 = 18,
    AutoLevelControl_3 = 19,
    NoiseGate = 20,
    LeftADCVolume = 21,
    RightADCVolume = 22,
    AdditionalControl_1 = 23,
    AdditionalControl_2 = 24,
    PwrMgmt_1 = 25,
    PwrMgmt_2 = 26,
    AdditionalControl_3 = 27,
    Unknown_28 = 28,
    Unknown_29 = 29,
    Unknown_30 = 30,
    ADCInputMode = 31,
    LeftADCSignalPath = 32,
    RightADCSignalPath = 33,
    LeftOutMix_1 = 34,
    LeftOutMix_2 = 35,
    RightOutMix_1 = 36,
    RightOutMix_2 = 37,
    MonoOutMix_1 = 38,
    MonoOutMix_2 = 39,
    LeftOut2Volume = 40,
    RightOut2Volume = 41,
    MonoOutVolume = 42,
    RegMax = 43
};

// 0F08
// first 32 entries appear to be for headphones
// and second 32 are for speakers
char g_volumeTable[] = {
    0x7F, 0x49, 0x46, 0x42, 0x3D, 0x3B, 0x39, 0x37, //  0 -  7
    0x35, 0x33, 0x31, 0x2F, 0x2D, 0x2B, 0x29, 0x27, //  8 - 15
    0x25, 0x23, 0x21, 0x1F, 0x1D, 0x1B, 0x19, 0x17, // 16 - 23
    0x15, 0x13, 0x11, 0x0F, 0x0D, 0x0B, 0x09, 0x7F, // 24 - 31
    0x1E, 0x1D, 0x1C, 0x1B, 0x1A, 0x19, 0x18, 0x17, // 32 - 39
    0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 0x0F, // 40 - 47
    0x0E, 0x0D, 0x0C, 0x0B, 0x0A, 0x09, 0x08, 0x07, // 48 - 55
    0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00, 0x00  // 56 - 63
};

// 0F50
Codec g_codec =
{
    -1, {
    0xFF68, 0xFF68, 0x0180, 0x0180,
    0xFFFF, 0x0000, 0xFFFF, 0x0002,
    0xFFFF, 0xFFFF, 0xFF00, 0xFF00,
    0xFFF0, 0xFFF0, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFF84, 0xFFFF, 0xFFCD,
    0xFFFF, 0xFF3C, 0xFF3C, 0x00C1,
    0xFFFF, 0x01C0, 0x0060, 0xFFFF,
    0xFF6B, 0xFFFF, 0xFFFF, 0xFFFF,
    0x0128, 0x0108, 0x0100, 0xFFAF,
    0xFFAF, 0x0100, 0x0050, 0x0050,
    0x0180, 0x0180, 0xFF86 },
    0,
    0,
    0,
    0,
    0x01FF,
    0,
    0
};

s32 sysEvHandler(s32 ev_id, char* ev_name, void* param, s32* result);

// 0FB4
SceSysEventHandler g_sysEv = {
    0x40,
    "SceCodec",
    0x00FFFF00,
    sysEvHandler,
    0,
    0,
    NULL,
    {0, 0, 0, 0, 0, 0, 0, 0, 0}
};

SCE_MODULE_INFO("sceWM8750_Driver", SCE_MODULE_KERNEL | SCE_MODULE_ATTR_CANT_STOP | SCE_MODULE_ATTR_EXCLUSIVE_LOAD
                                    | SCE_MODULE_ATTR_EXCLUSIVE_START, 1, 7);
SCE_MODULE_BOOTSTART("sceCodecInitEntry");
SCE_MODULE_REBOOT_BEFORE("sceCodecStopEntry");
SCE_SDK_VERSION(SDK_VERSION);

int doI2cTransaction(int reg, short value)
{
    u8 sp[2];
    g_codec.shadowRegs[reg] = value;
    sp[0] = (reg << 1) | (value >> 8);
    sp[1] = value;
    return sceI2cMasterTransmit(52, sp, 2);
}

int writeCodecRegister(int reg, short value)
{
    if (reg < 0 || reg >= RegMax)
        return SCE_ERROR_INVALID_INDEX;
    if (g_codec.ready <= 0)
        return 0;
    if (g_codec.shadowRegs[reg] == value)
        return 0;
    return doI2cTransaction(reg, value);
}

void setGpio5State(int set)
{
    if (set == 0) {
        // 0C4
        sceGpioPortSet(32);
    }
    else
        sceGpioPortClear(32);
}

void clearGpio1(void)
{
    sceGpioPortClear(2);
}

void setGpio1(void)
{
    sceGpioPortSet(2);
}

int sub_0110()
{
    sceGpioSetPortMode(5, 0);
    setGpio5State(0);
    sceGpioSetPortMode(1, 0);
    clearGpio1();
    return 0;
}

void initCodecHW()
{
    int ret = 0;
    if (g_codec.ready != 0)
        return;
    ret = doI2cTransaction(Reset, 1);
    g_codec.shadowRegs[Reset] = -1;
    g_codec.ready = 1;
    // 019C
    // Write default (or restore?) values to codec registers
    // negative values indicate that register should be skipped, 
    // but the shadow copy set to its inverse for future use
    int i;
    for (i = 0; i < 43; i++)
    {
        if (ret < 0)
            return;
        if (g_codec.shadowRegs[i] < 0)
        {
            // 01C8
            g_codec.shadowRegs[i] = ~g_codec.shadowRegs[i];
        }
        else
            ret = doI2cTransaction(i, g_codec.shadowRegs[i]);
        // 01D4
    }
    g_codec.flag = 0;
}

// arg 3 > 0, (re)init hardware
// arg 3 == 0, set some flags
// arg 3 < 0, clear args and flags
int sub_01FC(int arg0, int arg1, int arg2, int arg3)
{
    int flag1 = 0;
    int flag2 = 0;
    int ret = sceKernelLockMutex(g_codec.mutexId, 1, NULL);
    if (ret < 0)
        return ret;
    char flag = g_codec.flag;
    if (arg3 >= 0)
    {
        // 027C
        if (arg3 > 0 && (flag & 1) == 0) {
            initCodecHW(0);
            flag |= 1;
        }
        // 0298
        if (arg2 <= 0 && (arg2 != 0 || (flag & 8) == 0))
        {
            flag &= 0xFFFFFFF7;
        }
        else
        {
            flag |= 0x8;
            // 02B8
            flag2 |= 0xFE;
        }
    }
    else
    {
        flag = 0;
        arg1 = -1;
        arg0 = -1;
        flag2 = 1;
        // 02C0
        flag &= 0xFFFFFFF7;
    }
    // 02C4
    if (arg0 <= 0 && (arg0 != 0 || (flag & 4) == 0))
    {
        flag &= 0xFFFFFFFB;
    }
    else
    {
        flag |= 4;
        // 02E4
        flag1 = 0x60;
    }
    // 02E8
    if (arg1 <= 0 && (arg1 != 0 || (flag & 2) == 0))
        flag &= 0xFFFFFFFD;
    else
    {
        flag |= 2;
        // 0308
        flag1 |= 0x1A;
    }
    // 030C
    if ((flag & 6) == 0)
        flag2 |= 0x140;
    else
    {
        flag2 |= 0xC0;
        flag1 |= 0x180;
    }
    // 0320
    if ((flag & 4) == 0) {
        setGpio5State(0);
    }
    // 0338
    if ((flag & 2) == 0)
        clearGpio1();
    // 0348
    ret = writeCodecRegister(PwrMgmt_2, flag1 & g_codec.nineBitMask);
    if (ret >= 0)
    {
        if ((flag & 7) != 0 && g_codec.flag >= 0) {
            sceKernelDelayThread(100000);
            flag |= 0x80;
        }
        // 038C
        ret = writeCodecRegister(PwrMgmt_1, flag2);
        if (ret >= 0)
        {
            if ((flag & 4) != 0)
                setGpio5State(1);
            // 03B4
            if ((flag & 2) != 0)
                setGpio1();
        }
    }
    // (03C4)
    // 03C8
    g_codec.flag = flag;
    sceKernelUnlockMutex(g_codec.mutexId, 1);
    return ret;
}

int sceCodecOutputEnable(int arg0, int arg1)
{
    g_codec.outputDisabled = ((arg0 | arg1) == 0);
    if ((arg0 | arg1) != 0)
    {
        int ret = sub_01FC(arg0 * 2 - 1, arg1 * 2 - 1, 0, 1);
        if (ret < 0)
            return ret;
    }
    // 0460
    return sceCodecSetOutputVolume(g_codec.volumeIndex);
}

// index is of range [0, 31)
int sceCodecSetOutputVolume(int index)
{
    if (index < 0 || index >= 31)
        return SCE_ERROR_INVALID_INDEX;
    int tableIndex = 0;
    if (g_codec.outputDisabled == 0)
        tableIndex = index;
    // volumeTable is *always* zero
    int ret = sceCodecSetHeadphoneVolume(-g_volumeTable[g_codec.volumeTable * 31 + tableIndex]);
    if (ret >= 0)
    {
        // this seems like an off by one error, likely should be 32 + tableIndex
        ret = sceCodecSetSpeakerVolume(-g_volumeTable[31 + tableIndex]);
        if (ret >= 0)
            g_codec.volumeIndex = index;
    }
    // 050C
    return ret;
}

// volume is expected to be of range (-128, 128)
int sceCodecSetHeadphoneVolume(int volume)
{
    int level = pspMax(volume + g_codec.volumeOffset + 121, 0);
    if (level >= 128)
        return SCE_ERROR_INVALID_VALUE;
    int ret = sceKernelLockMutex(g_codec.mutexId, 1, NULL);
    if (ret < 0)
        return ret;
    // store left headphone level (level is unchanged)
    // and enable change gain on zero cross only
    ret = writeCodecRegister(LeftOut1Volume, level | 0x80); 
    if (ret >= 0)
    {
        // set right headphone level, enable change gain on zero cross only,
        // and update left level from stored value
        ret = writeCodecRegister(RightOut1Volume, level | 0x180);
        if (ret >= 0)
        {
            // 05C0
            sceKernelUnlockMutex(g_codec.mutexId, 1);
            return 0;
        }
    }
    // 05AC
    sceKernelUnlockMutex(g_codec.mutexId, 1);
    return ret;
}

// volume is expected to be of range (-128, 128)
int sceCodecSetSpeakerVolume(int volume)
{
    // hardware supports 80 steps, values 0x30 (-67dB) to 0x7F (+6dB)
    // less than 0x30 is analog mute
    // default level is 121 (0dB)
    int level = volume + 121;
    if (level >= 128)
        return SCE_ERROR_INVALID_VALUE;
    level += g_codec.volumeOffset;
    level = pspMin(level, 0x7F);
    level = pspMax(level, 0);
    int ret = sceKernelLockMutex(g_codec.mutexId, 1, NULL);
    if (ret < 0)
        return ret;
    // store left speaker level (level is unchanged)
    // and enable change gain on zero cross only
    ret = writeCodecRegister(LeftOut2Volume, level | 0x80);
    if (ret >= 0)
    {
        // set right speaker level, enable change gain on zero cross only,
        // and update left level from stored value
        ret = writeCodecRegister(RightOut2Volume, level | 0x180);
        if (ret >= 0)
        {
            // 0688
            sceKernelUnlockMutex(g_codec.mutexId, 1);
            return 0;
        }
    }
    // 0674
    sceKernelUnlockMutex(g_codec.mutexId, 1);
    return ret;
}

int sceCodecSetVolumeOffset(char arg0)
{
    g_codec.volumeOffset = arg0;
    sceCodecSetOutputVolume(g_codec.volumeIndex);
    return 0;
}

int sceCodecOutputDisable(void)
{
    return sub_01FC(-1, -1, 0, 0);
}

int sceCodec_driver_FCA6D35B(int freq)
{
    int sampleRate = g_codec.shadowRegs[SampleRate] & 0x180;
    if (freq != 44100 && freq != 48000) {
        // 0748
        return SCE_ERROR_INVALID_VALUE;
    }
    if (freq == 44100)
    {
        // 0740
        sampleRate |= 0x20;
        // 0750
    }
    // 0754
    int ret = sceKernelLockMutex(g_codec.mutexId, 1, NULL);
    if (ret < 0)
        return ret;
    ret = writeCodecRegister(SampleRate, sampleRate);
    sceKernelUnlockMutex(g_codec.mutexId, 1);
    return ret;
}

int sceCodec_driver_6FFC0FA4(char __attribute__((unused)) arg0)
{
    int ret = sub_01FC(0, 0, 1, 1);
    if (ret < 0)
        return ret;
    return 1;
}

int sceCodec_driver_A88FD064(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5)
{
    int ret;
    if (arg0 >= 0)
    {
        arg0 = 43;
        arg1 = (arg1 * 4 + 69) / 3;
        arg1 = pspMax(arg1, 0);
        arg1 = pspMin(arg1, 63);
        arg1 += 256;
    }
    else
    {
        // 0854
        arg0 = (arg0 * 2 + 57) / 3;
        arg0 = pspMax(arg0, 0);
        arg0 = pspMin(arg0, 15);
        arg0 = (arg0 & 0xFFFFFF8F) | ((pspMin(pspMax((arg1 / 6) + 2, 0), 7) << 4) & 0x70);
        arg0 += 128;
        arg1 = 279;
    }
    // 08B8
    arg2 = pspMin(arg2, 0);
    if (arg2 != 0)
    {
        arg2 = (arg2 * 2 + 153) / 3;
        arg2 = pspMax(arg2, 0);
        arg2 = pspMin(arg2, 31);
        arg2 = (arg2 << 3) + 1;
    }
    // 08FC
    ret = sceKernelLockMutex(g_codec.mutexId, 1, NULL);
    if (ret < 0)
        return ret;
    ret = writeCodecRegister(AutoLevelControl_1, 123);
    if (ret < 0)
        return ret;
    ret = doI2cTransaction(LeftInputVolume, arg1);
    if (ret < 0)
        return ret;
    ret = doI2cTransaction(RightInputVolume, arg1);
    if (ret < 0)
        return ret;
    ret = writeCodecRegister(AutoLevelControl_1, arg0);
    if (ret < 0)
        return ret;
    ret = writeCodecRegister(NoiseGate, arg2);
    if (ret < 0)
        return ret;
    ret = writeCodecRegister(AutoLevelControl_2, pspMin(pspMax(arg3, 0), 15));
    if (ret >= 0)
        ret = writeCodecRegister(AutoLevelControl_3, (pspMin(pspMax(arg5, 0), 10) & 0xFFFFFF0F) | ((pspMin(pspMax(arg4, 0), 10) << 4) & 0xF0));
    // 09C0
    sceKernelUnlockMutex(g_codec.mutexId, 1);
    return ret;
}

int sceCodec_driver_277DFFB6(void)
{
    return sub_01FC(0, 0, -1, 0);
}

// 0A28
s32 sysEvHandler(s32 ev_id, char* ev_name __attribute__((unused)), void* param __attribute__((unused)), s32* result __attribute__((unused)))
{
    switch (ev_id)
    {
    case 0x200:
        // 0A84
        sub_01FC(-1, -1, -1, 0);
        g_codec.shadowRegs[PwrMgmt_1] = 0x1C0;
        g_codec.ready = -1;
        g_codec.shadowRegs[LeftOut1Volume] = 0x80;
        g_codec.shadowRegs[RightOut1Volume] = 0x180;
        break;

    case 0x4003:
        // 0AB8
        sceGpioDisableTimerCapture(1, 2);
        sceGpioDisableTimerCapture(5, 2);
        g_codec.ready = 0;
        g_codec.flag = 0;
        break;

    case 0x10003:
        sub_0110();
        break;

    default:
        break;
    }
    return 0;
}

void sceCodec_driver_376399B6(int enable)
{
    if (!enable)
        sceSysregAudioClkoutClkDisable();
    else
        sceSysregAudioClkoutClkEnable();
}

int sceCodecInitEntry()
{
    for (;;)
        ;
    sub_0110();
    initCodecHW(1);
    g_codec.mutexId = sceKernelCreateMutex("SceCodec", 1, 0, NULL);
    if (g_codec.mutexId <= 0)
        return 1;
    sceKernelRegisterSysEventHandler(&g_sysEv);
    return 0;
}

int sceCodecSelectVolumeTable(int arg0)
{
    // volume table is only ever allowed to be zero, 
    // was this different in older FW versions?
    if (arg0 != 0)
        return SCE_ERROR_INVALID_INDEX;
    g_codec.volumeTable = 0;
    sceCodecSetOutputVolume(g_codec.volumeIndex);
    return 0;
}

int sceCodec_driver_E61A4623()
{
    return 0;
}

int sceCodec_driver_FC355DE0()
{
    return 0;
}

int sceCodecStopEntry(void *arg0 __attribute__((unused)), s32 arg1 __attribute__((unused)), s32 arg2 __attribute__((unused)), s32 arg3 __attribute__((unused)))
{
    sub_01FC(-1, -1, -1, -1);
    sceKernelUnregisterSysEventHandler(&g_sysEv);
    if (g_codec.mutexId >= 0)
        sceKernelDeleteMutex(g_codec.mutexId);
    // 0C14
    sceSysregAudioClkoutIoDisable();
    sceSysregAudioClkoutClkDisable();
    return 0;
}


/* Copyright (C) The uOFW team
   See the file COPYING for copying permission.
*/

#ifndef POWER_USER_H
#define	POWER_USER_H

#include "common_header.h"
#include "power_error.h"

/** @defgroup User User
 *  @ingroup PowerLibrary
 *
 *  The Power service User API.
 * @{
 */


 /* Callbacks */

/**
 * This constant specifies that a search for a slot number from among the empty slots is to be automatically performed
 * when a callback is registered with the ::scePowerRegisterCallback() function.
 */
#define SCE_POWER_CALLBACKSLOT_AUTO					(-1)

 /**
  * Defines constants passed to the ::ScePowerCallback function specifying the reason for the callback.
  */
typedef enum {
	/** These bits represent the remaining battery capacity in [%].*/
	SCE_POWER_CALLBACKARG_BATTERY_CAP = 0x0000007F,
	/** Indicates a battery has been equipped.  */
	SCE_POWER_CALLBACKARG_BATTERYEXIST = 0x00000080,
	/** Indicates the battery is in a low battery state.  */
	SCE_POWER_CALLBACKARG_LOW_BATTERY = 0x00000100,
	/** Indicates power is being supplied from an external power source (AC adapter). */
	SCE_POWER_CALLBACKARG_POWER_ONLINE = 0x00001000,
	/**
	 * Indicates the PSP's suspend process has begun. This happens for example when
	 *	- the user quickly presses the HOLD switch
	 *	- automatic sleep happens to save power
	 *	- forced suspension starts due to battery running out
	 */
	 SCE_POWER_CALLBACKARG_SUSPENDING = 0x00010000,
	 /** Indicates the PSP's resume process has started. */
	 SCE_POWER_CALLBACKARG_RESUMING = 0x00020000,
	 /** Indicates the PSP's resume process has completed. */
	 SCE_POWER_CALLBACKARG_RESUME_COMP = 0x00040000,
	 /**
	  * Indicates that standby operation has been started by pressing
	  * and holding the POWER switch.
	  */
	  SCE_POWER_CALLBACKARG_STANDINGBY = 0x00080000,
} ScePowerCallbackArg;

/**
 * Power service callback function prototype
 *
 * @param count Number of times the callback has been called.
 * @param arg The callback argument.
 * @param common Custom callback value. Specified by the same parameter in ::sceKernelCreateCallback().
 *
 * @return Always SCE_ERROR_OK.
 */
typedef void (*ScePowerCallback)(int count, int arg, void *common);

/**
 * Registers a power service notification callback.
 *
 * @param slot The callback registration slot to use. Specify either a value between 0 - 15 or ::SCE_POWER_CALLBACKSLOT_AUTO.
 * @param cbid The callback UID obtained by ::SceKernelCreateCallback().
 *
 * @return SCE_ERROR_OK when @slot was set to ::SCE_POWER_CALLBACKSLOT_AUTO and registration succeeded.
 * @return 0 - 15 on success when specific slot was used.
 * @return A value < 0 on failure.
 */
s32 scePowerRegisterCallback(s32 slot, SceUID cbid);

/**
 * Cancels a registered power service notification callback.
 *
 * @param slot The slot of the callback to unregister. Specify a value between 0 - 15.
 *
 * @return SCE_ERROR_OK on success, otherwise < 0.
 */
s32 scePowerUnregisterCallback(s32 slot);

s32 scePowerSetCallbackMode(s32 slot, s32 mode);

s32 scePowerGetCallbackMode(s32 slot, s32 *pMode);

/* Clock frequency functions */

/**
 * Get the CPU clock frequency.
 *
 * @return The CPU clock frequency in MHz.
 */
s32 scePowerGetCpuClockFrequencyInt(void);

/**
 * Get the CPU clock frequency.
 *
 * @remark The accuracy is identical to ::scePowerGetCpuClockFrequencyInt().
 *
 * @return The CPU clock frequency in MHz.
 */
float scePowerGetCpuClockFrequencyFloat(void);

/**
 * Get the bus clock frequency.
 *
 * @remark The bus clock frequency always operates at 1/2 the PLL clock frequency.
 *
 * @return The current bus clock frequency in MHz.
 */
s32 scePowerGetBusClockFrequencyInt(void);

/**
 * Get the bus clock frequency.
 *
 * @remark The bus clock frequency always operates at 1/2 the PLL clock frequency.
 * @remark The accuracy is identical to ::scePowerGetBusClockFrequencyInt().
 *
 * @return The current bus clock frequency in MHz.
 */
float scePowerGetBusClockFrequencyFloat(void);

/**
 * Get the PLL output clock frequency.
 *
 * @return The current PLL output clock frequency in MHz.
 */
s32 scePowerGetPllClockFrequencyInt(void);

/**
 * Get the PLL output clock frequency.
 *
 * @remark The accuracy is identical to ::scePowerGetPllClockFrequencyInt().
 *
 * @return The current PLL output clock frequency in MHz.
 */
float scePowerGetPllClockFrequencyFloat(void);

/**
 * Set clock frequencies.
 *
 * @remark This is an alias for ::scePowerClockFrequency() on firmwares earlier than 2.80.
 *
 * @see ::scePowerClockFrequency() for more details.
 *
 */
s32 scePowerSetClockFrequencyBefore280(s32 pllFrequency, s32 cpuFrequency, s32 busFrequency);

/**
 * Set clock frequencies.
 *
 * @remark This is an alias for ::scePowerClockFrequency() on firmware 2.80.
 *
 * @see ::scePowerClockFrequency() for more details.
 *
 */
s32 scePowerSetClockFrequency280(s32 pllFrequency, s32 cpuFrequency, s32 busFrequency);

/**
 * Set clock frequencies.
 *
 * @remark This is an alias for ::scePowerClockFrequency() on firmware 3.00.
 *
 * @see ::scePowerClockFrequency() for more details.
 *
 */
s32 scePowerSetClockFrequency300(s32 pllFrequency, s32 cpuFrequency, s32 busFrequency);

/**
 * Set clock frequencies.
 *
 * @remark This is an alias for ::scePowerClockFrequency() on firmware 3.50.
 *
 * @see ::scePowerClockFrequency() for more details.
 *
 */
s32 scePowerSetClockFrequency350(s32 pllFrequency, s32 cpuFrequency, s32 busFrequency);

/**
 * Set clock frequencies.
 *
 * @param pllFrequency The PLL clock frequency in MHh. Specify either 190, 222, 266 or 333.
 * @param cpuFrequency The CPU clock frequency in MHz. Specify a value between 1 - 333. Valid values have
 * to be less than or equal to the value specified for @p pllFrequency.
 * @param busFrequency The bus clock frequency in MHz. Must be exactly 1/2 of @p pllFrequency. In case of
 * 333 MHZ specified for @p pllFrequency, specify 166.
 *
 * @return SCE_ERROR_OK on success, otherwise < 0.
 */
s32 scePowerSetClockFrequency(s32 pllFrequency, s32 cpuFrequency, s32 busFrequency);


 /** @} */

#endif	/* POWER_USER_H */

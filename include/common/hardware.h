/* Copyright (C) 2011, 2012, 2013 The uOFW team
   See the file COPYING for copying permission.
*/

#ifndef COMMON_INCLUDED
# error "Only include common_imp.h or common_header.h!"
#endif

#define HW(addr) (*(vs32 *)(addr))
#define HWPTR(addr) ((vs32 *)(addr))

#define RAM_TYPE_32_MB          (1)
#define RAM_TYPE_64_MB          (2)
#define HW_RAM_SIZE             0xBC100040

#define HW_TIMER_0              0xBC500000
#define HW_TIMER_1              0xBC500010
#define HW_TIMER_2              0xBC500020
#define HW_TIMER_3              0xBC500030

#define HW_RESET_VECTOR         0xBFC00000
#define HW_RESET_VECTOR_SIZE    (0x1000)

#define HW_PERIPH_RESET         0xBC10004C
#define HW_RESET_TOP            (1UL << 0)
#define HW_RESET_SC             (1UL << 1)
#define HW_RESET_ME             (1UL << 2)
#define HW_RESET_AW             (1UL << 3)
#define HW_RESET_VME            (1UL << 4)
#define HW_RESET_AVC            (1UL << 5)
#define HW_RESET_USB            (1UL << 6)
#define HW_RESET_ATA            (1UL << 7)
#define HW_RESET_MSIF0          (1UL << 8)
#define HW_RESET_MSIF1          (1UL << 9)
#define HW_RESET_KIRK           (1UL << 10)
//#define HW_RESET_UNK          (1UL << 11) // no references found yet
#define HW_RESET_ATA_HDD        (1UL << 12)
#define HW_RESET_USB_HOST       (1UL << 13)
#define HW_RESET_UNK2           (1UL << 14) // sceSysreg_driver_0x0995F8F6(0) and sceSysreg_driver_0xC6C75585(0)
#define HW_RESET_UNK3           (1UL << 15) // sceSysreg_driver_0x0995F8F6(1) and sceSysreg_driver_0xC6C75585(1)
#define HW_RESET_UNK4           (1UL << 16) // sceSysreg_driver_0x32E02FDF and sceSysreg_driver_0x72887197

#define HW_BUSCLOCK_ENABLE      0xBC100050
#define HW_BUSCLOCK_ME          (1UL << 0)
#define HW_BUSCLOCK_AW_REG_A    (1UL << 1)
#define HW_BUSCLOCK_AW_REG_B    (1UL << 2)
#define HW_BUSCLOCK_AW_EDRAM    (1UL << 3)
#define HW_BUSCLOCK_DMAC_PLUS   (1UL << 4)
#define HW_BUSCLOCK_VME         (1UL << 5) // re-verify, set from me_t2img 0x083018fc, cleared from me_t2img 0x08301918
//#define HW_BUSCLOCK_UNK_1     (1UL << 6)
#define HW_BUSCLOCK_KIRK        (1UL << 7)
#define HW_BUSCLOCK_ATA         (1UL << 8)
#define HW_BUSCLOCK_USB         (1UL << 9)
#define HW_BUSCLOCK_MSIF0       (1UL << 10)
#define HW_BUSCLOCK_MSIF1       (1UL << 11)
#define HW_BUSCLOCK_EMC_DDR     (1UL << 12)
#define HW_BUSCLOCK_EMC_SMBUS   (1UL << 13)
#define HW_BUSCLOCK_APB         (1UL << 14)
#define HW_BUSCLOCK_AUDIO_0     (1UL << 15)
#define HW_BUSCLOCK_AUDIO_1     (1UL << 16)
#define HW_BUSCLOCK_ATA_HDD     (1UL << 17)
#define HW_BUSCLOCK_USB_HOST    (1UL << 18)
#define HW_BUSCLOCK_UNK_2       (1UL << 19) // sceSysreg_driver_0x3BB0B2C8(0) (set), sceSysreg_driver_0x76E57DC6(0) (clear)
#define HW_BUSCLOCK_UNK_3       (1UL << 20) // sceSysreg_driver_0x3BB0B2C8(1) (set), sceSysreg_driver_0x76E57DC6(1) (clear)

#define HW_CLOCK_1_ENABLE       0xBC100054
#define HW_CLOCK_ATA            (1UL << 0)
#define HW_CLOCK_ATA_HDD        (1UL << 1)
//#define HW_CLOCK_UNK1         (1UL << 2)
//#define HW_CLOCK_UNK2         (1UL << 3)
#define HW_CLOCK_UNK3           (1UL << 4) // sceSysreg_driver_0xC9585F8E (clear), sceSysreg_driver_0xFC0131A7 (set)
//#define HW_CLOCK_UNK4         (1UL << 5)
//#define HW_CLOCK_UNK5         (1UL << 6)
#define HW_CLOCK_UNK6           (1UL << 7) // sceSysreg_driver_0xC9585F8E (clear), sceSysreg_driver_0xFC0131A7 (set)
#define HW_CLOCK_MSIF0          (1UL << 8)
#define HW_CLOCK_MSIF1          (1UL << 9)
//#define HW_CLOCK_UNK7         (1UL << 10)
//#define HW_CLOCK_UNK8         (1UL << 11)
#define HW_CLOCK_EMC_DDR        (1UL << 12)
//#define HW_CLOCK_UNK9         (1UL << 13)
//#define HW_CLOCK_UNK10        (1UL << 14)
//#define HW_CLOCK_UNK11        (1UL << 15)
#define HW_CLOCK_USB_HOST       (1UL << 16)
//#define HW_CLOCK_UNK12        (1UL << 17)
//#define HW_CLOCK_UNK13        (1UL << 18)
//#define HW_CLOCK_UNK14        (1UL << 19)
#define HW_CLOCK_UNK15          (1UL << 20) // sceSysreg_driver_0xA7C82BDD(0) (set), sceSysreg_driver_0xFF0E07B1(0) (clear)
#define HW_CLOCK_UNK16          (1UL << 21) // sceSysreg_driver_0xA7C82BDD(1) (set), sceSysreg_driver_0xFF0E07B1(1) (clear)

#define HW_CLOCK_2_ENABLE       0xBC100058
#define HW_CLOCK_SPI_0          (1UL << 0)
#define HW_CLOCK_SPI_1          (1UL << 1)
#define HW_CLOCK_SPI_2          (1UL << 2)
#define HW_CLOCK_SPI_3          (1UL << 3)
#define HW_CLOCK_SPI_4          (1UL << 4)
#define HW_CLOCK_SPI_5          (1UL << 5)
#define HW_CLOCK_UART_0         (1UL << 6)
#define HW_CLOCK_UART_1         (1UL << 7)
#define HW_CLOCK_UART_2         (1UL << 8)
#define HW_CLOCK_UART_3         (1UL << 9)
#define HW_CLOCK_UART_4         (1UL << 10)
#define HW_CLOCK_UART_5         (1UL << 11)
#define HW_CLOCK_APB_TIMER_0    (1UL << 12)
#define HW_CLOCK_APB_TIMER_1    (1UL << 13)
#define HW_CLOCK_APB_TIMER_2    (1UL << 14)
#define HW_CLOCK_APB_TIMER_3    (1UL << 15)
#define HW_CLOCK_AUDIO_0        (1UL << 16)
#define HW_CLOCK_AUDIO_1        (1UL << 17)
#define HW_CLOCK_LCDC           (1UL << 18)
#define HW_CLOCK_PWM            (1UL << 19)
#define HW_CLOCK_UNK0           (1UL << 20) // sysreg FUN_00000798 (set), FUN_000007a4 (clear)
#define HW_CLOCK_IIC            (1UL << 21)
#define HW_CLOCK_SIRCS          (1UL << 22)
#define HW_CLOCK_GPIO           (1UL << 23)
#define HW_CLOCK_AUDIO_CLKOUT   (1UL << 24)
#define HW_CLOCK_UNK1           (1UL << 25) // sceSysreg_driver_0xB6296512 (clear), sceSysreg_driver_0xF9C93DD4 (set)

#define HW_CLOCK_SELECT_1       0xBC10005C
#define HW_CLOCK_SEL_MSIF0      (3UL << 0)
#define HW_CLOCK_SEL_MSIF1      (3UL << 2)
#define HW_CLOCK_SEL_ATA        (3UL << 4)
#define HW_CLOCK_SEL_ATA_HDD    (3UL << 8)
#define HW_CLOCK_SEL_UNK0_0     (3UL << 10) // sceSysreg_driver_0xC2F3061F(0, 0-2)
#define HW_CLOCK_SEL_UNK0_1     (3UL << 12) // sceSysreg_driver_0xC2F3061F(0, 0-2)

#define HW_CLOCK_SELECT_2       0xBC100060
#define HW_CLOCK_SEL_APB_TIMER_0 (7UL << 0)
// 1 bit hole at bit 3
#define HW_CLOCK_SEL_APB_TIMER_1 (7UL << 4)
// 1 bit hole at bit 7
#define HW_CLOCK_SEL_APB_TIMER_2 (7UL << 8)
// 1 bit hole at bit 11
#define HW_CLOCK_SEL_AUDIO_0     (1UL << 16)
#define HW_CLOCK_SEL_AUDIO_1     (1UL << 17)
//#define HW_CLOCK_SEL_LCDC
//#define HW_CLOCK_SEL_UNK1
//#define HW_CLOCK_SEL_UNK2

// there appears to be 1-bit holes between each SPI instance,
// presumably this is for convenience of addressing
#define HW_CLOCK_SELECT_3       0xBC100064
#define HW_CLOCK_SEL_SPI_0      (3UL << 0)
#define HW_CLOCK_SEL_SPI_1      (3UL << 4)
#define HW_CLOCK_SEL_SPI_2      (3UL << 8)
#define HW_CLOCK_SEL_SPI_3      (3UL << 12)
#define HW_CLOCK_SEL_SPI_4      (3UL << 16)
#define HW_CLOCK_SEL_SPI_5      (3UL << 20)

#define HW_PLL_CONFIG           0xBC100068
#define HW_PLL_OUT_SEL          (7UL << 0)
//int sceSysregPllUpdateFrequency()
//
#define HW_PLL_MULTIPLIER_CFG   0xBC1000FC
// bits 0-7 unknown
// bits 8-16 pll multipliers

#define HW_IO_ENABLE            0xBC100078
//#define HW_IO_UNK0            (1UL << 0)
#define HW_IO_EMCSM             (1UL << 1)
#define HW_IO_USB               (1UL << 2)
#define HW_IO_ATA               (1UL << 3)
#define HW_IO_MSIF0             (1UL << 4)
#define HW_IO_MSIF1             (1UL << 5)
#define HW_IO_LCDC              (1UL << 6)
#define HW_IO_AUDIO_0           (1UL << 7)
#define HW_IO_AUDIO_1           (1UL << 8)
#define HW_IO_IIC               (1UL << 9)
#define HW_IO_SIRCS             (1UL << 10)
#define HW_IO_AUDIOCLKOUT       (1UL << 11)
//#define HW_IO_UNK1            (1UL << 12)
#define HW_IO_PWM               (1UL << 13)
#define HW_IO_ATA_HDD           (1UL << 14)
#define HW_IO_UNK2              (1UL << 15) // sceSysreg_driver_0x6F3B6D7D and sceSysreg_driver_0x87B61303 (both set), sceSysreg_driver_0x87B6130 (clear)
#define HW_IO_UART_0            (1UL << 16)
#define HW_IO_UART_1            (1UL << 17)
#define HW_IO_UART_2            (1UL << 18)
#define HW_IO_UART_3            (1UL << 19)
#define HW_IO_UART_4            (1UL << 20)
#define HW_IO_UART_5            (1UL << 21)
#define HW_IO_UNK3              (1UL << 22) // sceSysreg_driver_19F4C92D(0) (set), sceSysreg_driver_DA5B5ED9(0) (clear)
#define HW_IO_UNK4              (1UL << 23) // sceSysreg_driver_19F4C92D(1) (set), sceSysreg_driver_DA5B5ED9(1) (clear)
#define HW_IO_SPI_0             (1UL << 24)
#define HW_IO_SPI_1             (1UL << 25)
#define HW_IO_SPI_2             (1UL << 26)
#define HW_IO_SPI_3             (1UL << 27)
#define HW_IO_SPI_4             (1UL << 28)
#define HW_IO_SPI_5             (1UL << 29)
#define HW_IO_UNK5              (1UL << 30) // sceSysreg_driver_0x0607A4C4 (set), sceSysreg_driver_0x803E5F37 (clear)

#define HW_FUSE_ID_UPPER        0xBC100090
#define HW_FUSE_ID_LOWER        0xBC100094

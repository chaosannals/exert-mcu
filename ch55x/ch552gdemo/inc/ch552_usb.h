#ifndef CH55X_USB_H
#define CH55X_USB_H

#include <compiler.h>

SFR(USB_C_CTRL, 0x91);
#define bVBUS2_PD_EN      0x80      // USB VBUS2 10K pulldown resistance: 0=disable, 1=enable pullup
#define bUCC2_PD_EN       0x40      // USB CC2 5.1K pulldown resistance: 0=disable, 1=enable pulldown
#define bUCC2_PU1_EN      0x20      // USB CC2 pullup resistance control high bit
#define bUCC2_PU0_EN      0x10      // USB CC2 pullup resistance control low bit
#define bVBUS1_PD_EN      0x08      // USB VBUS1 10K pulldown resistance: 0=disable, 1=enable pullup
#define bUCC1_PD_EN       0x04      // USB CC1 5.1K pulldown resistance: 0=disable, 1=enable pulldown
#define bUCC1_PU1_EN      0x02      // USB CC1 pullup resistance control high bit
#define bUCC1_PU0_EN      0x01      // USB CC1 pullup resistance control low bit

SFR(USB_INT_FG, 0xD8);
SBIT(U_IS_NAK, 0xD8, 6); // ReadOnly: indicate current USB transfer is NAK received
SBIT(U_TOG_OK, 0xD8, 5); // ReadOnly: indicate current USB transfer toggle is OK
SBIT(U_SIE_FREE, 0xD8, 4); // ReadOnly: indicate USB SIE free status
SBIT(UIF_FIFO_OV, 0xD8, 3); // FIFO overflow interrupt flag for USB, direct bit address clear or write 1 to clear
SBIT(UIF_SUSPEND, 0xD8, 2); // USB suspend or resume event interrupt flag, direct bit address clear or write 1 to clear
SBIT(UIF_TRANSFER, 0xD8, 1); // USB transfer completion interrupt flag, direct bit address clear or write 1 to clear
SBIT(UIF_BUS_RST, 0xD8, 0); // bus reset event interrupt flag, direct bit address clear or write 1 to clear

SFR(USB_INT_ST, 0xD9);
SFR(USB_MIS_ST, 0xDA);
SFR(USB_RX_LEN, 0xDB);
SFR(USB_INT_EN, 0xE1);
SFR(USB_CTRL, 0xE2);
SFR(USB_DEV_AD, 0xE3);


#endif

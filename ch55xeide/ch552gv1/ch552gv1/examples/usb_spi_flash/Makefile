TARGET = usb_spi_flash

# Adjust the XRAM location and size to leave space for the USB DMA buffers
# Buffer layout in XRAM:
# 0x0000 Ep0Buffer[8]
# 0x0040 Ep1Buffer[8]
# 0x0080 EP2Buffer[2*64]
#
# This takes a total of 256bytes, so there are 768 bytes left.
XRAM_SIZE = 0x0300
XRAM_LOC = 0x0100

C_FILES = \
	main.c \
	usb_spi_flash.c \
	spi_flash.c \
	../../include/debug.c \
	../../include/spi.c

pre-flash:
	@-echo "E" > /dev/ttyACM0 #使其跳转到Bootloader
	sleep 1
	

include ../Makefile.include

PATH_TOOLS?=
include $(PATH_TOOLS)/Makefile
BOARD=rpi_pico
DTS_OVERLAY=./boards/rpi_pico.overlay
SERIAL=/dev/ttyUSB0
FBAUD?=921600 # FBAUD: seleccionar velocidad en baudios para flashear esp32

west-espressif:
	west update
	west blobs fetch hal_espressif

west-espressif-openocd:
	west espressif install

# west-esp-update:
# 	west espressif update
flash:
	. ./environment.bash && \
	west flash --esp-baud-rate $(FBAUD) || \
		(echo "\nNo fue posible flashear el dispositivo\n")

environment:
	/bin/bash $(PATH_TOOLS)/zephyr-env.sh $(BOARD)

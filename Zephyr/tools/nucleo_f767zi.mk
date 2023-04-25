PATH_TOOLS?=
include ../tools/Makefile
BOARD=nucleo_f767zi
DTS_OVERLAY?=./boards/nucleo_f767zi_dts.overlay
SERIAL?=/dev/ttyACM0

environment:
	/bin/bash $(PATH_TOOLS)/zephyr-env.sh default

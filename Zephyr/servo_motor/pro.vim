source ../tools/vim-prj-esp32-zephyr.vim
 
" e src/servo_handlers.c
" :Nread https://github.com/zephyrproject-rtos/hal_espressif/blob/zephyr/include/dt-bindings/pinctrl/esp32-pinctrl.h
e $ZEPHYR_BASE/../modules/hal/espressif/include/dt-bindings/pinctrl/esp32-pinctrl.h
e boards/esp32.overlay
e $ZEPHYR_BASE/dts/bindings/pwm/espressif,esp32-ledc.yaml
e $ZEPHYR_BASE/drivers/pwm/pwm_led_esp32.c
" e $ZEPHYR_BASE/include/zephyr/drivers/led.h
" e $ZEPHYR_BASE/drivers/led/led_pwm.c
" e src/servo.h
e src/main.c


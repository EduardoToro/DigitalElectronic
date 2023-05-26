# Ejemplo de uso de servomotores

Para ver las diferentes combinaciones de canales y gpio para los pwm observe la información en el siguiente enlace: [esp32-pinctrl.h](https://github.com/zephyrproject-rtos/hal_espressif/blob/zephyr/include/dt-bindings/pinctrl/esp32-pinctrl.h)

Las funciones usadas en el **main.c** están documentadas en [pwh.h](https://docs.zephyrproject.org/latest/hardware/peripherals/pwm.html#)

Ejemplo:

```dts
  <LEDC_CH0_GPIO2>,
  <LEDC_CH1_GPIO4>,
  <LEDC_CH2_GPIO5>,
  <LEDC_CH3_GPIO18>,
  <LEDC_CH4_GPIO19>,
  <LEDC_CH5_GPIO21>,
  <LEDC_CH6_GPIO22>,
  <LEDC_CH7_GPIO23>,
  <LEDC_CH8_GPIO15>
```

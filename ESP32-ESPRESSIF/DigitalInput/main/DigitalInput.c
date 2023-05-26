#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

#define LEDPIN 27
#define BTNPIN 14 

void app_main(void)
{
    int ledState = 0; 

    //Inicializar Pin
    gpio_reset_pin(LEDPIN); 

    //Definir la dirección: Salida
    gpio_set_direction(LEDPIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(BTNPIN, GPIO_MODE_INPUT);

    gpio_set_level(LEDPIN, ledState);

    while (1)
    {
        ledState = gpio_get_level(BTNPIN);
        gpio_set_level(LEDPIN, ledState);
    }
}
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LedPin 4
#define BlinkTime 1000

void app_main(void)
{
    int ledState = 0; 

    //Inicializar Pin
    gpio_reset_pin(LedPin); 

    //Definir la dirección: Salida
    gpio_set_direction(LedPin, GPIO_MODE_OUTPUT);

    while (1)
    {
        gpio_set_level(LedPin, ledState);
        ledState = !ledState; 
        vTaskDelay(BlinkTime / portTICK_PERIOD_MS);
    }
}

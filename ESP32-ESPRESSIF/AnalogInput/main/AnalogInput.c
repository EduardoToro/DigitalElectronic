#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"


void app_main(void)
{
    //Variable para almacenar los valores leidos tal cual
    int32_t raw_value;

    //Configuración del canal
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11); 
    adc1_config_width(ADC_WIDTH_BIT_12); 

    //Lectura de los datos
    while (1)
    {
        //Valor puro del resultado de la conversión
        raw_value = adc1_get_raw(ADC1_CHANNEL_6);
        printf("adc raw: %ld\n", raw_value); 
        vTaskDelay(1000 / portTICK_PERIOD_MS); 
    }
}
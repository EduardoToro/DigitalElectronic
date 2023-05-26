#include <stdio.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"

#define EXAMPLE_ADC1_CHAN0 ADC_CHANNEL_6
#define EXAMPLE_ADC_ATTEN ADC_ATTEN_DB_11

//Variables Definition
#define R2 100000
#define A 0.7768951640E-3
#define B 2.068786810E-4
#define C 1.280087096E-7 
#define KELVINCONSTANT 273.15


//Function Declaration
float AdcToCelsius(int adcIn);

adc_oneshot_unit_handle_t adc1_handle;

adc_oneshot_unit_init_cfg_t init_config1 = {
    .unit_id = ADC_UNIT_1,
    .ulp_mode = ADC_ULP_MODE_DISABLE,
};

adc_oneshot_chan_cfg_t config = {
    .atten = EXAMPLE_ADC_ATTEN, 
    .bitwidth = ADC_BITWIDTH_12,
};

static int ntc_value; 

void app_main(void)
{
    //Inicialización ADC1
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));

    //Configuración ADC1
    adc_oneshot_config_channel(adc1_handle, EXAMPLE_ADC1_CHAN0, &config);

    while (1)
    {
        ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, EXAMPLE_ADC1_CHAN0, &ntc_value)); 
        float tempCelsius = AdcToCelsius(ntc_value); 
        printf("NTC VALUE: %d  TEMP: %f\n", ntc_value, tempCelsius);
        vTaskDelay(1000 / portTICK_PERIOD_MS); 
    }

    adc_oneshot_del_unit(adc1_handle);  
}

float AdcToCelsius(int adcIn){ 
    int resistanceNTC = (adcIn * R2) / (4095 - adcIn); 
    float logNTC = log(resistanceNTC); 
    float temp = 1 / (A + (B * logNTC) + (C * logNTC * logNTC * logNTC));
    temp = temp - KELVINCONSTANT; 

    return temp; 
}
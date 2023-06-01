#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "driver/ledc.h"

#define LEDC_TIMER  LEDC_TIMER_0      //Timer de control
#define LEDC_MODE   LEDC_HIGH_SPEED_MODE       //Modo de velocidad
#define LEDC_OUTPUT 25     //Pin de saida
#define LEDC_CHANNEL LEDC_CHANNEL_0    //Canal de control
#define LEDC_DUTY_RES LEDC_TIMER_12_BIT   //Resolucion en bits
#define LEDC_DUTY 0        //Valor inicial
#define LEDC_FREQUENCY 5000  //Frecuencia de funcionamiento
#define LEDC_HPOINT 0   //Ajuste de fase


void app_main(void)
{
    //Configuracion del timer
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE, 
        .timer_num = LEDC_TIMER, 
        .duty_resolution = LEDC_DUTY_RES,
        .freq_hz = LEDC_FREQUENCY, 
        .clk_cfg = LEDC_AUTO_CLK
    }; 
    ledc_timer_config(&ledc_timer); 

    //Configuracion de canal
    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .timer_sel = LEDC_CHANNEL,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LEDC_OUTPUT,
        .duty = LEDC_DUTY, 
        .hpoint = LEDC_HPOINT
    }; 
    ledc_channel_config(&ledc_channel); 

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

        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, raw_value); 
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL); 

        vTaskDelay(1000 / portTICK_PERIOD_MS); 
    }
}
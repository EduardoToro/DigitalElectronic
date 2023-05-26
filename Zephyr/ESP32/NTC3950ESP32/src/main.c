//Library Declaration
#include <stdio.h>
#include <math.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>

//Variable Declaration
double R2 = 100000;
double A = 0.7768951640E-3;
double B = 2.068786810E-4;
double C = 1.280087096E-7;
double KELVINCONSTANT = 273.15;

//Variable Connection
#define ADC_NODE DT_PHANDLE(DT_PATH(zephyr_user), io_channels)
#define ADC_CHANNEL DT_IO_CHANNELS_INPUT_BY_IDX(DT_PATH(zephyr_user), 0)
#define ADC_RESOLUTION 12
#define SLEEP_TIME_MS 1000
uint16_t sample_buffer;


//Structure Declaration
const struct device *dev_adc = DEVICE_DT_GET(ADC_NODE);
struct adc_sequence sequence = {
    .channels = BIT(ADC_CHANNEL),
    .buffer = &sample_buffer,
    .buffer_size = sizeof(sample_buffer),
    .resolution = ADC_RESOLUTION,
};

//Function Declaration 
float AdcToCelsius(double adcIn);

void main(void){
    //Connection Check
    if (!device_is_ready(dev_adc))
    {
        printf("ADC device not found\n");
        return;
    }
    printf("ADC device found\n");

    //Start of reading
    while (1)
    {
        adc_read(dev_adc, &sequence); 
        float tempCelsius = AdcToCelsius(sample_buffer); 
        printk("NTC VALUE: %d  TEMP: %f\n", sample_buffer, tempCelsius);
        k_msleep(SLEEP_TIME_MS); 
    }
    

}

float AdcToCelsius(double adcIn){ 
    double resistanceNTC = (adcIn * R2) / (4095 - adcIn); 
    double logNTC = resistanceNTC; 
    double temp = 1 / (A + (B * logNTC) + (C * logNTC * logNTC * logNTC));
    temp = temp - KELVINCONSTANT;

    return temp; 
}





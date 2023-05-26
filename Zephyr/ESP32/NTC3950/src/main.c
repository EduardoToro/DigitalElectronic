//Library Declaration
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <stdio.h>
#include <math.h>
#include "NTC3950.c"

// //Variable Declaration
// #define ADC_NODE DT_PHANDLE(DT_PATH(zephyr_user), io_channels)
// #define ADC_CHANNEL DT_IO_CHANNELS_INPUT_BY_IDX(DT_PATH(zephyr_user), 0)
// #define ADC_RESOLUTION 12
// uint16_t sample_buffer;


// //Structure Declaration
// const struct device *dev_adc = DEVICE_DT_GET(ADC_NODE);
// struct adc_sequence sequence = {
//     .channels = BIT(ADC_CHANNEL),
//     .buffer = &sample_buffer,
//     .buffer_size = sizeof(sample_buffer),
//     .resolution = ADC_RESOLUTION,
// };
// /*static const struct adc_channel_cfg ch0_cfg_dt = 
//     ADC_CHANNEL_CFG_DT(DT_CHILD(DT_NODELABEL(adc0), 6));*/


void main(void){
    // if (!device_is_ready(dev_adc))
    // {
    //     printf("ADC device not found\n");
    //     return;
    // }
    printf("ADC device found\n");
    double temp = getTemp(10);
}





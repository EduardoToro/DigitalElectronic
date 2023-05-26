#ifndef NTC3950
#define NTC3950

//Library Declaration
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <stdio.h>

#define ADC_NODE DT_PHANDLE(DT_PATH(zephyr_user), io_channels)
#define ADC_CHANNEL DT_IO_CHANNELS_INPUT_BY_IDX(DT_PATH(zephyr_user), 0)
#define ADC_RESOLUTION 12

extern uint16_t sample_buffer;
extern const struct device *dev_adc = DEVICE_DT_GET(ADC_NODE);
extern struct adc_sequence adc_sequence = {
        .channels = BIT(ADC_CHANNEL),
        .buffer = &sample_buffer,
        .buffer_size = sizeof(sample_buffer),
        .resolution = ADC_RESOLUTION,
    };
#endif
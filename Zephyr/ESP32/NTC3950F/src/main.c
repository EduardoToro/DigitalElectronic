//C Libraries
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>

//Zephyr Librarys
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

//Verification
#if !DT_NODE_EXISTS(DT_PATH(zephyr_user)) || \
	!DT_NODE_HAS_PROP(DT_PATH(zephyr_user), io_channels)
#error "No suitable devicetree overlay specified"
#endif

//Variable Declaration
double R2 = 100000;
double A = 0.7768951640E-3;
double B = 2.068786810E-4;
double C = 1.280087096E-7;
double KELVINCONSTANT = 273.15;

/* Data of ADC io-channels specified in devicetree. */
#define DT_SPEC_AND_COMMA(node_id, prop, idx) \
	ADC_DT_SPEC_GET_BY_IDX(node_id, idx),
static const struct adc_dt_spec adc_channels[] = {
	DT_FOREACH_PROP_ELEM(DT_PATH(zephyr_user), io_channels, DT_SPEC_AND_COMMA)
};

//Function Declaration
double AdcToCelsius(int32_t adcIn);

void main(void)
{
	int err;
	uint16_t buf = 0;
	struct adc_sequence sequence = {
		.buffer = &buf,
		.buffer_size = sizeof(buf),
	};

	/* Configure channels individually prior to sampling. */
	for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) {
		if (!device_is_ready(adc_channels[i].dev)) {
			printk("ADC controller device not ready\n");
			return;
		}

		err = adc_channel_setup_dt(&adc_channels[i]);
		if (err < 0) {
			printk("Could not setup channel #%d (%d)\n", i, err);
			return;
		}
	}

	while (1) {
		printk("ADC reading:\n");
		for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) {
			int32_t val_mv;

			printk("- %s, channel %d: ",
			       adc_channels[i].dev->name,
			       adc_channels[i].channel_id);

			(void)adc_sequence_init_dt(&adc_channels[i], &sequence);


			err = adc_read(adc_channels[i].dev, &sequence);
			if (err < 0) {
				printk("Could not read (%d)\n", err);
				continue;
			} else {
				printk("%"PRIu16, buf);
			}

			//Espacio de prueba 
			float resistanceNTC = (float)(buf * R2) / (buf - val_mv);


			//Impresion de pruebas
			printk("%f", resistanceNTC); 

			/* conversion to mV may not be supported, skip if not */
			val_mv = buf;
			err = adc_raw_to_millivolts_dt(&adc_channels[i], &val_mv);
			if (err < 0) {
				printk(" (value in mV not available)\n");
			} else {
				printk(" = %"PRId32" mV\n", val_mv);
			}

			k_sleep(K_MSEC(1000));
		}
	}
}

double AdcToCelsius(int32_t adcIn){ 
    //double resistanceNTC = (adcIn * R2) / (4095 - adcIn); 
    //double logNTC = log(resistanceNTC); 
    //double temp = 1 / (A + (B * logNTC) + (C * logNTC * logNTC * logNTC));
	//double temp = 1 / (A + (B + (C * resistanceNTC * resistanceNTC)) * resistanceNTC); 
    //temp = temp - KELVINCONSTANT;
	double temp = adcIn; 

    return temp; 
}
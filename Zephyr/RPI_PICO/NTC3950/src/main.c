 //############## ADC #######################

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

#if !DT_NODE_EXISTS(DT_PATH(zephyr_user)) || \
	!DT_NODE_HAS_PROP(DT_PATH(zephyr_user), io_channels)
#error "No suitable devicetree overlay specified"
#endif

#define DT_SPEC_AND_COMMA(node_id, prop, idx) \
	ADC_DT_SPEC_GET_BY_IDX(node_id, idx),

/* Data of ADC io-channels specified in devicetree. */
static const struct adc_dt_spec adc_channels[] = {
	DT_FOREACH_PROP_ELEM(DT_PATH(zephyr_user), io_channels,
			     DT_SPEC_AND_COMMA)
};

//Variable Declaration
long R2 = 100000;
long A = 0.7768951640E-3;
long B = 2.068786810E-4;
long C = 1.280087096E-7;
long KELVINCONSTANT = 273.15;

//Function Declaration
int AdcToCelsius(long resistanceNTC);
long GetResistenceNTC(uint32_t adcIn);
long AverageResis(long res); 

void main(void)
{
	 //############## MAIN ADC #######################
	int err;
	uint16_t buf;
	uint32_t prueba; 
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
		//############# INIT ADC ####################
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

			prueba = buf; 
			//Valor resistencia
			long resistance = GetResistenceNTC(prueba);
			//Promedio de la resistencia
			long avgResistence = AverageResis(resistance);
			printk(" = Resistencia NTC %ld", avgResistence);

			//Valor temperatura
			int temp = AdcToCelsius(avgResistence); 
			printk(" = Temp %d", temp);

			/* conversion to mV may not be supported, skip if not */
			val_mv = buf;
			err = adc_raw_to_millivolts_dt(&adc_channels[i],
						       &val_mv);
			if (err < 0) {
				printk(" (value in mV not available)\n");
			} else {
				printk(" = %"PRId32" mV\n", val_mv);
			}
		}
		k_sleep(K_MSEC(1000));
	}
}

long GetResistenceNTC(uint32_t adcIn){ 
    //long resistanceNTC = (adcIn * R2) / (1256 - adcIn);
    //long logNTC = ilog2(resistanceNTC); 
    //long temp = 1 / (A + (B * logNTC) + (C * logNTC * logNTC * logNTC)); 
    //temp = temp - KELVINCONSTANT;
	long resistanceNTC = (adcIn * R2) / (1234 - adcIn);
	//long logNTC = log(resistanceNTC); 

    return resistanceNTC; 
}

int AdcToCelsius(long resistanceNTC){
	int temp; 
	if (resistanceNTC <= 321240 && resistanceNTC >= 227764)
	{
		temp = 5; 
	}else if (resistanceNTC < 227764&& resistanceNTC >= 179724)
	{
		temp = 10; 
	}else if (resistanceNTC < 179724 && resistanceNTC >= 142748)
	{
		temp = 15; 
	}else if (resistanceNTC < 142748 && resistanceNTC >= 109152)
	{
		temp = 20;
	}else if (resistanceNTC < 109152 && resistanceNTC >= 91697)
	{
		temp = 25;
	}else if (resistanceNTC < 91697 && resistanceNTC >= 74115)
	{
		temp = 30;
	}else if (resistanceNTC < 74115 && resistanceNTC >= 60222)
	{
		temp = 35;
	}else if (resistanceNTC < 60222 && resistanceNTC >= 49183)
	{
		temp = 40;
	}else if (resistanceNTC < 49183 && resistanceNTC >= 40364)
	{
		temp = 45;
	}else if (resistanceNTC < 40364 && resistanceNTC >= 33284)
	{
		temp = 50;
	}else if (resistanceNTC < 33284 && resistanceNTC >= 27573)
	{
		temp = 55;
	}else if (resistanceNTC < 27573)
	{
		temp = 60;
	}
	
	return temp; 
}

long AverageResis(long res){
	long sum = 0;
	long average; 
	for (int i = 0; i < 10; i++)
	{
		sum += res; 
	}
	average = sum / 10; 

	return average; 
}
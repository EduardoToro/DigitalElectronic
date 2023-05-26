/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(blink, CONFIG_LOG_DEFAULT_LEVEL);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void main(void)
{
	int ret;
	/* if (!device_is_ready(led.port)) { */
	/* 	return; */
	/* } */

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
    LOG_ERR("No fue posible configurar el pin como una salida gpio-leds");
		return;
	}
  LOG_INF("GPIO ha sido configirado como un gpio-led");

	while (1) {
		ret = gpio_pin_toggle_dt(&led);
		if (ret < 0) {
      LOG_ERR("Fallá al intercambiar el valor salida del LED");
			return;
		}
    LOG_INF("blink");
		k_msleep(SLEEP_TIME_MS);
	}
}

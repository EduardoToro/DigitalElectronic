/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "push_button" alias. */
#define PUSH_BUTTON_NODE DT_ALIAS(push_button)
/* #if !DT_NODE_HAS_STATUS(push-button, okay) */
/* #error "Unsupported board: push-button devicetree alias is not defined" */
/* #endif */

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec push_button = GPIO_DT_SPEC_GET_OR(PUSH_BUTTON_NODE, gpios,
							      {0});
/* GPIO END */  

void main(void)
{

	int err;

    /* GPIO START */
	int ret;
	if (!device_is_ready(push_button.port)) {
		printk("Error: push_button device %s is not ready\n",
		       push_button.port->name);
		return;
	}

	ret = gpio_pin_configure_dt(&push_button, GPIO_INPUT);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",
		       ret, push_button.port->name, push_button.pin);
		return;
	}

	while (1)
  {
    int val = gpio_pin_get_dt(&push_button);
    printk("push push_button value: [%d]\n", val);
		k_msleep(SLEEP_TIME_MS);
	}
}

/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file Sample app to demonstrate PWM-based servomotor control
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h> /* Acá se encuentran las funciones usadas en este ejemplo. Las funciones están documentadas en: https://docs.zephyrproject.org/latest/hardware/peripherals/pwm.html# */

static const struct pwm_dt_spec servo = PWM_DT_SPEC_GET(DT_NODELABEL(servo0));
static const uint32_t min_pulse = DT_PROP(DT_NODELABEL(servo0), min_pulse);
static const uint32_t max_pulse = DT_PROP(DT_NODELABEL(servo0), max_pulse);

#define STEP PWM_USEC(25)
#define STEP_TIME K_MSEC(50) // Tiempo por paso (Solo requerido para este ejemplo de barrido

enum direction {
	DOWN,
	UP,
};

void main(void)
{
	uint32_t pulse_width = min_pulse;
	enum direction dir = UP;
	int ret;

	printk("Servomotor control\n");

	if (!device_is_ready(servo.dev)) {
		printk("Error: PWM device %s is not ready\n", servo.dev->name);
		return;
	}

	while (1) {
		ret = pwm_set_pulse_dt(&servo, pulse_width);
		if (ret < 0) {
			printk("Error %d: failed to set pulse width\n", ret);
			return;
		}

		if (dir == DOWN) {
			if (pulse_width <= min_pulse) {
				dir = UP;
				pulse_width = min_pulse;
			} else {
				pulse_width -= STEP;
			}
		} else {
			pulse_width += STEP;

			if (pulse_width >= max_pulse) {
				dir = DOWN;
				pulse_width = max_pulse;
			}
		}

		k_sleep(STEP_TIME);
	}
}

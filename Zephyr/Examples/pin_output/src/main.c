/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(out_put, CONFIG_LOG_DEFAULT_LEVEL);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   500

/* The devicetree node identifier for the "pin_output" alias. */
#define PIN_OUT_NODE DT_ALIAS(pin_output)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec pin_output = GPIO_DT_SPEC_GET(PIN_OUT_NODE, gpios);

void main(void)
{
  /* Variable auxiar ret (return) permite monitorear las respuestas de las funciones */
  /* si las funciones retornan 0 es porque la tarea solicitada fue cumplida satisfactoriamente. */
	int ret;

	if (!device_is_ready(pin_output.port)) {
    /* Si ret es diferente de 0 termina la ejecución de la función main */
    LOG_ERR("Puerto en el gpio%d no está listo", pin_output.pin);
		return;
	}

  /* GPIO configurado como SALIDA y con un valor inicial 0 */
	ret = gpio_pin_configure_dt(&pin_output, GPIO_OUTPUT_LOW);

  /* GPIO configurado como SALIDA y con un valor inicial 1 */
	/* ret = gpio_pin_configure_dt(&pin_output, GPIO_OUTPUT_ACTIVE); */

	if (ret < 0) {
    /* Si ret es diferente de 0 termina la ejecución de la función main */
		return;
    LOG_ERR("No puede configurar el gpio%d como salida", pin_output.pin);
	}

	while (1) {

    /* Activa solo una de las opciones que se muestran a continuación */
    /* Ambas opciones son equivalentes. */

    /* ################ */
    /*  START OPTION 2 */
    /* ################ */
    gpio_pin_set_dt(&pin_output, 0);
		k_msleep(SLEEP_TIME_MS);
    LOG_INF("gpio%d en valor: 0", pin_output.pin);

    gpio_pin_set_dt(&pin_output, 1);
		k_msleep(SLEEP_TIME_MS);
    LOG_INF("gpio%d en valor: 1", pin_output.pin);
    /* END */
    /* ################ */

    /* ################ */
    /*  START OPTION 2 */
    /* ################ */
		/* ret = gpio_pin_toggle_dt(&pin_output); */
		/* if (ret < 0) { */
		/* 	return; */
		/* } */
		/* k_msleep(SLEEP_TIME_MS); */
    /* END */
    /* ################ */
  }
}

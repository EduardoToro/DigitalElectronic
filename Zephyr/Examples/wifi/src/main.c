
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <stdio.h>

#include "wifi.h"

LOG_MODULE_REGISTER(main, CONFIG_LOG_DEFAULT_LEVEL);

void main(void)
{
	LOG_INF("WiFi demo");

	wifi_connect();

}


#include <zephyr/kernel.h>
#include <stdio.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, CONFIG_LOG_DEFAULT_LEVEL);
/* LOG_MODULE_REGISTER(main, CONFIG_LOG_DEFAULT_LEVEL); */
/* LOG_MODULE_DECLARE(main, CONFIG_LOG_DEFAULT_LEVEL); */

#include "wifi.h"
#include "dhcp.h"
#include "tcp_client.h"

void main(void)
{
	LOG_INF("WiFi demo");

	wifi_connect();

  dhcpv4_startup();

	LOG_INF("Should have DHCPv4 lease at this point.");

  LOG_INF("Start tcp_client_start");

  k_msleep(1000);

  tcp_client_start();

}

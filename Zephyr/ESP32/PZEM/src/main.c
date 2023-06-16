#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

//Variable Declaration
uint8_t cmd_read_voltage[] = {0xF8, 0x04, 0x00, 0x00, 0x00, 0x0A, 0x64, 0x64};
uint8_t rx_buf[25];
float voltage, current;

/* change this to any other UART peripheral if desired */
#define UART_DEVICE_NODE DT_ALIAS(uart2)

static const struct device *const uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);

void main(void)
{
	if (!device_is_ready(uart_dev)) {
		printk("UART device not found!");
		return;
	}

	while (1)
	{
		int ret_tx = uart_tx(uart_dev, cmd_read_voltage, sizeof(cmd_read_voltage), SYS_FOREVER_MS); 
		if (ret_tx != 0)
		{
			printk("Fallo el envio de datos!\n"); 
		}
		printf("TX0: %d", cmd_read_voltage[0]);
		printf(" = TX1: %d", cmd_read_voltage[1]); 
		printf(" = TX2: %d", cmd_read_voltage[2]); 
		printf(" = TX3: %d", cmd_read_voltage[3]); 
		printf(" = TX4: %d\n", cmd_read_voltage[4]); 
		

		int ret_rx = uart_rx_enable(uart_dev, rx_buf, sizeof(rx_buf), SYS_FOREVER_MS);
		if (ret_rx != 0)
		{
			printk("Fallo la recepción de datos!\n"); 
		}

		printf("RX0: %d", rx_buf[0]); 
		printf(" = RX1: %d", rx_buf[1]); 
		printf(" = RX2: %d", rx_buf[2]); 
		printf(" = RX3: %d", rx_buf[3]); 
		printf(" = RX4: %d\n", rx_buf[4]); 

		voltage = (float)((rx_buf[3] << 8) | rx_buf[4]) / 10.0; 
		printf(" Voltage: %.2f V\n", voltage); 

		k_sleep(K_MSEC(1000));
	}
}
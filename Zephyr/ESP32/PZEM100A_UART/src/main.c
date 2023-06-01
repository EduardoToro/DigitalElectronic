#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

//Variable Declaration
uint8_t cmd_read_voltage[] = {0xB0, 0xC0, 0xA8, 0x01, 0x01, 0x00, 0x1A};
uint8_t cmd_read_current[] = {0xB1, 0xC0, 0xA8, 0x01, 0x01, 0x00, 0x1B};
uint8_t rx_buf[8];
float voltage, current; 

/* change this to any other UART peripheral if desired */
#define UART_DEVICE_NODE DT_ALIAS(uart0)

#define MSG_SIZE 8

/* queue to store up to 10 messages (aligned to 4-byte boundary) */
K_MSGQ_DEFINE(uart_msgq, MSG_SIZE, 10, 4);

static const struct device *const uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);

/* receive buffer used in UART ISR callback */
//static char rx_buf[MSG_SIZE];
static int rx_buf_pos;

/*
 * Read characters from UART until line end is detected. Afterwards push the
 * data to the message queue.
 */
void serial_cb(const struct device *dev, void *user_data)
{
	uint8_t c;

	if (!uart_irq_update(uart_dev)) {
		return;
	}

	if (!uart_irq_rx_ready(uart_dev)) {
		return;
	}

	/* read until FIFO empty */
	while (uart_fifo_read(uart_dev, &c, 1) == 1) {
		if ((c == '\n' || c == '\r') && rx_buf_pos > 0) {
			/* terminate string */
			rx_buf[rx_buf_pos] = '\0';

			/* if queue is full, message is silently dropped */
			k_msgq_put(&uart_msgq, &rx_buf, K_NO_WAIT);

			/* reset the buffer (it was copied to the msgq) */
			rx_buf_pos = 0;
		} else if (rx_buf_pos < (sizeof(rx_buf) - 1)) {
			rx_buf[rx_buf_pos++] = c;
		}
		/* else: characters beyond buffer size are dropped */
	}
}

/*
 * Print a null-terminated string character by character to the UART interface
 * Envia datos de micro a sensor
 */
void print_uart(char *buf)
{
	int msg_len = strlen(buf);

	for (int i = 0; i < msg_len; i++) {
		uart_poll_out(uart_dev, buf[i]);
	}
}

void main(void)
{
	char tx_buf[MSG_SIZE];

	if (!device_is_ready(uart_dev)) {
		printk("UART device not found!");
		return;
	}

	/* configure interrupt and callback to receive data */
	int ret = uart_irq_callback_user_data_set(uart_dev, serial_cb, NULL);

	if (ret < 0) {
		if (ret == -ENOTSUP) {
			printk("Interrupt-driven UART API support not enabled\n");
		} else if (ret == -ENOSYS) {
			printk("UART device does not support interrupt-driven API\n");
		} else {
			printk("Error setting UART callback: %d\n", ret);
		}
		return;
	}
	uart_irq_rx_enable(uart_dev);

	//print_uart("Hello! I'm your echo bot.\r\n");
	//print_uart("Tell me something and press enter:\r\n");
	
	//printf("Command: %hhn", cmd_read_voltage);

	//while (k_msgq_get(&uart_msgq, &tx_buf, K_FOREVER) == 0) {
	/*while (1) {
		printk("Command: %hhn", cmd_read_voltage);
		print_uart(cmd_read_voltage); 
		k_msgq_get(&uart_msgq, &tx_buf, K_FOREVER); 
		printf("Voltage: %s", tx_buf);
		printk("\r\n");
	}*/

	while (1)
	{
		uart_tx(uart_dev, cmd_read_voltage, sizeof(cmd_read_voltage), 1); 
		uart_rx_enable(uart_dev, rx_buf, sizeof(rx_buf), 1000); 
		//print_uart(rx_buf); 
		printf("POS1: %d\n", rx_buf[1]); 
		printf("POS2: %d\n", rx_buf[2]); 
		printf("POS3: %d\n", rx_buf[3]); 
		printf("POS4: %d\n", rx_buf[4]); 
		voltage = (float)((rx_buf[3] << 8) | rx_buf[4]) / 10.0; 
		printf(" Voltage: %.2f V\n", voltage); 

		k_sleep(K_MSEC(1000));
	}
}
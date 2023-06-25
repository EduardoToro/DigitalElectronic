#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

//Command for PZEM
uint8_t cmd_read[8] = {0xF8, 0x04, 0x00, 0x00, 0x00, 0x0A, 0x64, 0x64};

//Reception variables
#define BUFFER_SIZE 25
uint8_t buffer[BUFFER_SIZE];
size_t buffer_len = 0;
uint8_t rx_data;
float voltage, current;

//Processing of data obtained
void pzem_reading(uint8_t *data, size_t length)
{
    // Check if the received data matches the expected response format
    if (length == 24 && data[0] == 0x04 && data[1] == 0x14) {
        // Extract the relevant information from the received data
        voltage = (data[2] << 8 | data[3]) / 10.0;
		current = (data[4] << 8 | data[5] | data[6] << 24 | data[7] << 16) / 1000.0;

        // Print the extracted values
        printf("Voltage: %.1f V\n", voltage);
        printf("Current: %.2f A\n", current);
    }
}

int main(void)
{
	//Construction of the device 
	const struct device *uart_pzem = DEVICE_DT_GET(DT_NODELABEL(uart_pzem));

	//Device status check
	if (!device_is_ready(uart_pzem)) {
		printk("UART device not found!");
		return 0;
	}

	while (1) {
		//Send command
		//size_t command_length = sizeof(cmd_read) / sizeof(cmd_read[0]);

    	for (size_t i = 0; i < sizeof(cmd_read); i++) {
        	uart_poll_out(uart_pzem, cmd_read[i]);
    	}

		//Receive an answer
		int len = uart_poll_in(uart_pzem, &rx_data);

		//Verification of the reception status
		if (len == -1)
		{
			printk("No data to receive!\n");
		}else if (len == 0)
		{
			printk("Successful data reception!\n"); 
		}else
		{
			printk("Failure to receive data!\n"); 
		}

		//Read data until the end of the answer
		while (len == 0)
		{
			uart_poll_in(uart_pzem, &rx_data);
			buffer[buffer_len] = rx_data;
            buffer_len++;

			if (buffer_len == 24)
			{
				len = -1; 
			}
		}

		//Processing of read data
		pzem_reading(buffer, buffer_len);

		//Reset buffer for the next packet
		buffer_len = 0; 

		k_sleep(K_MSEC(1000));
	}
	return 0;
}
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

//Comandos para el PZEM
uint8_t cmd_read_voltage[8] = {0xF8, 0x04, 0x00, 0x00, 0x00, 0x0A, 0x64, 0x64};

//Variable de recepción
#define BUFFER_SIZE 25
float voltage, current;

void process_pzem_reading(uint8_t *data, size_t length)
{
    // Check if the received data matches the expected response format
    if (length == 24 && data[0] == 0x04 && data[1] == 0x14) {
        // Extract the relevant information from the received data
        voltage = (data[2] << 8 | data[3]) / 10.0;
		current = (data[4] << 8 | data[5] |data[6] << 24 |data[7] << 16) / 1000.0;

        // Print the extracted values
        printf("Voltage: %.1f V\n", voltage);
        printf("Current: %.2f A\n", current);
    }
}

int main(void)
{
	//Construcción del dispositivo
	const struct device *uart2 = DEVICE_DT_GET(DT_NODELABEL(uart_test));

	//Verificación del estado del dispositivo
	if (!device_is_ready(uart2)) {
		printk("UART device not found!");
		return 0;
	}

	//Nombre del dispositivo en pantalla
	printk("Device name is: %s\n", uart2->name);

	//Prueba de recepción
	uint8_t buffer[BUFFER_SIZE];
    size_t buffer_len = 0;

	while (1) {
		//Envia el comando
		size_t command_length = sizeof(cmd_read_voltage) / sizeof(cmd_read_voltage[0]);

    	for (size_t i = 0; i < command_length; i++) {
        	uart_poll_out(uart2, cmd_read_voltage[i]);
    	}

		//Recepción de la respuesta
		uint8_t rx_data;
		int len = uart_poll_in(uart2, &rx_data);

		if (len == -1)
		{
			printk("No hay datos para recibir!\n");
		}else if (len == 0)
		{
			printk("Recepción de datos exitosa!\n"); 
		}else
		{
			printk("Fallo la recepción de datos!\n"); 
		}

		while (len == 0)
		{
			uart_poll_in(uart2, &rx_data);
			buffer[buffer_len] = rx_data;
            buffer_len++;

			if (buffer_len == 24)
			{
				len = -1; 
			}
		}

		process_pzem_reading(buffer, buffer_len);

		for (size_t i = 0; i < buffer_len; i++) {
            printf("%02X ", buffer[i]);			
        }
        printf("\n");
		buffer_len = 0; 

		k_sleep(K_MSEC(2000));
	}
	return 0;
}

#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define UART_DEVICE_NAME DT_LABEL(DT_ALIAS(uart2))
#define UART_DEVICE_NODE DT_ALIAS(uart2)

void parse_pzem_data(const char *data)
{
    // Example data format: "V:235.67 I:2.34 P:550.21 E:1200.43"

    float voltage = 0.0;
    float current = 0.0;
    float power = 0.0;
    float energy = 0.0;

    // Use string manipulation functions to extract data fields
    char *token;
    char *rest = (char *)data;

    while ((token = strtok_r(rest, " ", &rest))) {
        if (strncmp(token, "V:", 2) == 0) {
            voltage = atof(token + 2);
        } else if (strncmp(token, "I:", 2) == 0) {
            current = atof(token + 2);
        } else if (strncmp(token, "P:", 2) == 0) {
            power = atof(token + 2);
        } else if (strncmp(token, "E:", 2) == 0) {
            energy = atof(token + 2);
        }
    }

    // Display the parsed data
    printf("Voltage: %.2fV\n", voltage);
    printf("Current: %.2fA\n", current);
    printf("Power: %.2fW\n", power);
    printf("Energy: %.2fWh\n", energy);
}

void uart_callback(const struct device *dev, struct uart_event *evt, void *user_data)
{
    if (evt->type == UART_RX_RDY) {
        // Handle received data here
        parse_pzem_data(evt->data.rx.buf);
    }
}

void main(void)
{
    const struct device *uart_dev;
    struct uart_event uart_evt;

    uart_dev = device_get_binding(UART_DEVICE_NODE);
    if (!uart_dev) {
        printf("Cannot bind UART device\n");
        return;
    }

    uart_event_callback_set(uart_dev, uart_callback, NULL);

    while (1) {
        // Send command to PZEM-004T V3 sensor to read all electrical parameters
        const char *command = "ReadAll";
        uart_tx(uart_dev, command, strlen(command), SYS_FOREVER_MS);

        // Wait for response
        uart_rx_enable(uart_dev, &uart_evt.data.rx_buf, 1, SYS_FOREVER_MS);
        k_sleep(K_MSEC(1000));  // Sleep for 1 second for the response to arrive
    }
}

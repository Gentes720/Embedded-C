
#include "uart.h"

int main(void)
{
    uart_init();

    uint16_t temperature = 27;
    uint16_t humidity = 65;
    uint8_t sensor_status = 0xA5;

    while (1)
    {
        uart_print("SENSOR DEBUG");
        uart_newline();

        uart_print("Temperature: ");
        uart_print_uint(temperature);
        uart_print(" C");
        uart_newline();

        uart_print("Humidity: ");
        uart_print_uint(humidity);
        uart_print(" %");
        uart_newline();

        uart_print("Sensor status: 0x");
        uart_print_hex(sensor_status);
        uart_newline();

        uart_newline();

        // Temporisation approximative
        for (volatile uint32_t i = 0; i < 3000000UL; i++)
        {
        }
    }
}

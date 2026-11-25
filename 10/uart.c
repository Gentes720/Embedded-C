
#include <avr/io.h>
#include <stdint.h>
#include "uart.h"


#define BAUD 9600UL

#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)

// Initialisation USART1
void uart_init(void)
{
    UBRR1H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR1L = (uint8_t)UBRR_VALUE;

    // Mode normal
    UCSR1A &= ~(1 << U2X1);

    // Activation de l'émetteur
    UCSR1B = (1 << TXEN1);

    // Format 8 bits, sans parité, 1 bit de stop
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
}

// Transmission d'un caractère
void uart_putchar(char c)
{
    while (!(UCSR1A & (1 << UDRE1)))
    {
        // Attendre que le registre soit vide
    }

    UDR1 = c;
}

// Transmission d'une chaîne
void uart_print(const char *s)
{
    while (*s != '\0')
    {
        uart_putchar(*s);
        s++;
    }
}

// Transmission d'un entier décimal
void uart_print_uint(uint16_t number)
{
    char digits[5];
    uint8_t i = 0;

    if (number == 0)
    {
        uart_putchar('0');
        return;
    }

    // Extraction des chiffres
    while (number > 0)
    {
        digits[i] = (number % 10) + '0';
        number /= 10;
        i++;
    }

    // Affichage dans l'ordre inverse
    while (i > 0)
    {
        i--;
        uart_putchar(digits[i]);
    }
}

// Transmission d'un octet en hexadécimal
void uart_print_hex(uint8_t number)
{
    const char hex_digits[] = "0123456789ABCDEF";

    uart_putchar(hex_digits[(number >> 4) & 0x0F]);
    uart_putchar(hex_digits[number & 0x0F]);
}

// Saut de ligne
void uart_newline(void)
{
    uart_putchar('\r');
    uart_putchar('\n');
}

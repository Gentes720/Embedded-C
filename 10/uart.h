
#ifndef UART_H
#define UART_H

#include <stdint.h>

// Initialisation UART1
void uart_init(void);

// Transmission d'un caractère
void uart_putchar(char c);

// Affichage d'une chaîne
void uart_print(const char *s);

// Affichage d'un entier non signé
void uart_print_uint(uint16_t number);

// Affichage d'un nombre hexadécimal
void uart_print_hex(uint8_t number);

// Saut de ligne
void uart_newline(void);

#endif

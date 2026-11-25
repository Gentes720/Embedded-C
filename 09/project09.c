
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define BAUD 9600L
// calcul du diviseur baud rate
#define UBRR_VALUE ((F_CPU / (16L * BAUD)) - 1)

void uart1_init(void){

    UBRR1 = (uint8_t)(UBRR_VALUE >> 8); 
    UBRR1L = (uint8_t)UBRR_VALUE; // 103

    // MODE NORMAL U2X1 = 0
    UCSR1A = 0;

    // ACTIVATION DE L'EMETEUR
    UCSR1B = (1 << TXEN1) ;

    // FORMAT: mode asynchrone, 8 bits, pas de parite

    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);

}

void uart1_putchar(char data){
    // attendre que le tampon soit vide
    while( !(UCSR1A & (1 << UDRE1))){
        // Attente active bloquante
    }

    // ecriture dans la tampon d'emission UDR1
    UDR1 = data;

}

void uart1_print(const char *str){
    while(*str){ // tant que le caractere pointe n'est pas '\0'
        uart1_putchar(*str);
        str++;
    }
}

int main(void){
    uart1_init();

    while(1) {
        uart1_print("Hello World of ES\r\n");
        _delay_ms(1000);
    }
}
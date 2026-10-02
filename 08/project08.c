// Project 8

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

int uart1_putchar(char c, FILE *stream) {
    (void)stream;
    if (c == '\n') {
        uart1_putchar('\r', NULL);
    }
    // CORRECTION : On utilise UCSR1A et UDRE1 pour l'USART1
    while (!(UCSR1A & (1 << UDRE1))) {}
    UDR1 = c; // Envoie sur le registre de l'USART1
    return 0;
}

FILE uart1_output = FDEV_SETUP_STREAM(uart1_putchar, NULL, _FDEV_SETUP_WRITE);

void uart1_init(void) {
    UBRR1H = 0;
    UBRR1L = 103; // 9600 bauds pour un clock de 16MHz
    UCSR1B |= (1 << TXEN1); // Active l'émetteur de l'USART1
    stdout = &uart1_output;  
}

void timer1BConfig(void){
    
    TCCR1B |= (1 << CS12) | (1 << CS10) | (1 << ICNC1) ;  // 1 0 1 for prescaler 1024, electric noise cancellation

    TIMSK1 |= (1 << ICIE1); //enable interrupt
}

void push_buttonConfig(void){
    DDRD &= ~(1 << PD4); 
    PORTD |= (1 << PD4);
}

volatile uint8_t time_ready = 0;
volatile uint16_t t_press = 0;
volatile uint16_t t_up = 0; 
volatile uint32_t total_time =0;

ISR(TIMER1_CAPT_vect){
    if (!(TCCR1B & (1 << ICES1))) { // if falling edge
        t_press = ICR1;
        TCCR1B |= (1 << ICES1); // trigger rising edge
    } else {
        t_up = ICR1;
        TCCR1B &= ~(1 << ICES1); // trigger falling edge again

        uint16_t pulse_count = t_up - t_press;
        total_time = ((uint32_t)pulse_count * 64) / 1000;// 64micro seconds per pulse for prescaler 1024

        time_ready = 1; 
    }
}


int main(void){
    uart1_init();
    timer1BConfig();
    push_buttonConfig();

    sei(); 

    while (1)
    {
        if (time_ready){
            time_ready = 0;
            printf("The button press duration is %lu milliseconds \n", total_time);
        }
    }
    
}
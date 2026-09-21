// Project 7

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void timer1BConfig(void){
    OCR1A = 31249;   //value for pre scaler 256/ 0.5 secs
    
    TCCR1B |= (1 << WGM12); // Bit 3 for WGM, 
    TCCR1B |= (1 << CS12); //Bit 2 for prescaler seletion

    TIMSK1 |= (1 << OCIE1A); //enable interrupt
}

void ledA0Config(void){
    DDRF |= (1 << PF0); 
}

ISR(TIMER1_COMPA_vect){
    PORTF ^= (1 << PF0);
}

int main(void){
    timer1BConfig();
    ledA0Config();
    sei();

    while (1)
    {}
    
}

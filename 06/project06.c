// Project 6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(INT0_vect){
    PORTF ^= (1 << PF2); // Toggle PF2
}

int main(void){

    DDRD &= ~(1 << PD0); // Set PD0 as input
    PORTD |= (1 << PD0); // Enable pull-up resistor on PD0

    DDRF |= (1 << PF2); // PF2 as output


    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00); // Configure INT0 to trigger on falling edge

    EIMSK |= (1 << INT0); // Enable INT0 interrupt in the mask

    // Enable global interrupts
    sei();

    while(1){
        _delay_ms(60000);
    }

}


//Project 5

#include <avr/io.h>
#include <util/delay.h>

volatile uint8_t duty_cycle = 0;
volatile int8_t direction = 1;
volatile uint8_t repeat_count = 0;

int main(void){
     // setting
    DDRF |= (1 << PF2); 
    DDRF |= (1 << PF3);


    while(1){
        
        for(uint8_t timer = 0; timer < 100; timer++){

            if (timer < duty_cycle) {
                PORTF |= (1 << PF2); // turn on LED
                PORTF |= (1 << PF3); // turn on LED
            } else {
                PORTF &= ~(1 << PF2); // turn off LED
                PORTF &= ~(1 << PF3); // turn off LED
            }
            _delay_us(30);
        }

        if (repeat_count > 9) {
            repeat_count = 0;

            duty_cycle += direction;

            if (duty_cycle >= 99) {
                direction = -1;
            } 
            if (duty_cycle <= 0) {
                direction = 1;
            }

        }else {
            repeat_count++;
        }

    }   
}
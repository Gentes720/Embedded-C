t 
//Project 4

#include <avr/io.h>
#include <util/delay.h>

volatile uint8_t counter = 0;

int main(void){
     // setting
    DDRF |= (1 << PF2); // PF2 -PF5 as output;
    DDRF |= (1 << PF3);
    DDRF |= (1 << PF4);
    DDRF |= (1 << PF5);

    DDRF &= ~(1 << PF0); // PF0 as Input

    PORTF |= (1 << PF0); //PULL-UP

    while(1){
        if (!(PINF & (1 << PF0))){
            _delay_ms(50);
            if (!(PINF & (1 << PF0))){

                counter = (counter + 1);

                PORTF = (PORTF & 0xC3) | ((counter << 2) & 0x3C);




                while (!(PINF & (1 << PF0))){

                }

            }
        }
    }

}

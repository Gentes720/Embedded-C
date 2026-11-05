
//Project 4

#include <avr/io.h>
#include <util/delay.h>

volatile uint8_t counter = 0;
int main(void){
    // pf2 -pf5 as output , pf0 input
    DDRF |= (1 << PF2) | (1 << PF3) | (1 << PF4) | (1 << PF5);

    DDRF &= ~(1 << PF0);
    PORTF |= ( 1 << PF0); 

    while(1){
        if (!(PINF & (1 << PF0))){
            _delay_ms(20);
            if (!(PINF & (1 << PF0))){
                if (counter <= 16){
                    counter += 1;
                }else{
                    counter = 0;
                }
            
                PORTF = (PORTF & 0xC3) | (counter << 2);

                while(!(PINF & (1 << PF0))){}
            }
        }
    }
}

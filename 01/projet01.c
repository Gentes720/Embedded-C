// PROJECT 01: BLINK A LED

#include<avr/io.h>
#include<util/delay.h>

int main(void)
{
    // Port PF0 Configuration as output
    DDRF |= (1 << PF0); 

    while(1){

        PORTF ^= (1 << PORT0); // Switch ON/OFF the LED
        _delay_ms(1000);// Wait 1s
    }
}


























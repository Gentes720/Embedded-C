//Progect 2
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // Port configuration
    DDRF = 0b00011100;

    while (1) {
        _delay_ms(500);
        PORTF = 0b00000100;
        _delay_ms(500);
        PORTF = 0b00001000;
        _delay_ms(500);
        PORTF = 0b00010000;
    }
    return 0;
}


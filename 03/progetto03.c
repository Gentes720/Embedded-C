
//Progetto 3

#include <avr/io.h>
#include <util/delay.h>

int main(void){
     // impostazione
    DDRF |= (1 << PF5); // PF5 come uscita;
    DDRF &= ~(1 << PF1); // INGRESSO

    PORTF |= (1 << PF1); //PULL-UP

    while(1){
        if (!(PINF & (1 << PF1))){
            _delay_ms(50);
            if (!(PINF & (1 << PF1))){
                PORTF ^= (1 << PF5); //toggle led


                while (!(PINF & (1 << PF1))){

                }

            }
        }
    }

}
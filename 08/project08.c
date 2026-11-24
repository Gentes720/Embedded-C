// PROJECT 8

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h> 


volatile uint16_t first_capture = 0;
volatile uint16_t second_capture = 0;
volatile uint16_t overflow_count = 0;
volatile uint8_t was_pressed = 0;
volatile uint8_t mesure_flag = 0;

void timer4_init(void) {
    // Prescaler 1024 + Noise canceler
    TCCR4B |= (1 << ICNC4) | (1 << CS42) | (1 << CS40);
    
    // Enable input capture AND overflow interrupts
    TIMSK4 |= (1 << ICIE4) | (1 << TOIE4);
    // TOIE4 : autorise interruption sur overflow
}

void components_init(void){
    // LED as output
    DDRF |= (1 << PF0) | (1 << PF1);
    // button as input
    DDRL &= ~(1 << PL0);// set PL0 as input
    PORTL |= (1 << PL0); // enable pull-up resistor
}


ISR(TIMER4_OVF_vect) {
    overflow_count++;  // Compter les overflows
}

ISR(TIMER4_CAPT_vect) {
    uint16_t capture_value = ICR4;
    
    if (was_pressed == 0) {
        // Premier front : APPUI (front descendant, ICES4=0)
        first_capture = capture_value;
        
        // Flip ICES4 : prochain front sera MONTANT (relâchement)
        TCCR4B ^= (1 << ICES4);
        
        was_pressed = 1;
    } else {
        // Deuxième front : RELÂCHEMENT (front montant, ICES4=1)
        second_capture = capture_value;
        
        // Flip ICES4 : prochain front sera DESCENDANT (appui)
        TCCR4B ^= (1 << ICES4);
        
        mesure_flag = 1;
        was_pressed = 0;
    }
}

int main(void) {
    components_init();
    timer4_init();
    sei();
    
    while(1) {
        if (mesure_flag) {
            mesure_flag = 0;
            
            
            // Section critique : copie atomique
            uint16_t local_first, local_second, local_overflow;
            cli();
            local_first = first_capture;
            local_second = second_capture;
            local_overflow = overflow_count;
            sei();
            
            // Calcul avec cast explicite
            uint32_t ticks = ((uint32_t)local_overflow * 65536UL) 
                           + (uint32_t)local_second 
                           - (uint32_t)local_first;
                           
            uint32_t time_ms = (ticks * 64UL) / 1000UL;
            
            if (time_ms < 300) {
                PORTF |= (1 << PF0);   // LED courte
                PORTF &= ~(1 << PF1);
            } else {
                PORTF |= (1 << PF1);   // LED longue
                PORTF &= ~(1 << PF0);
            }
            overflow_count = 0;
        }
    }
}

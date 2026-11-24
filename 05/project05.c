#include <avr/io.h>
#include <util/delay.h>

// Définition de la fréquence du microcontrôleur (nécessaire pour _delay_us)
// À adapter si votre horloge est différente (ex: 8000000UL pour 8 MHz)
#ifndef F_CPU
#define F_CPU 16000000UL 
#endif

// Masque pour regrouper les opérations sur PF2 et PF3
#define LED_MASK ((1 << PF2) | (1 << PF3))

volatile uint8_t duty_cycle = 0;
volatile int8_t direction = 1;
volatile uint8_t repeat_count = 0;

int main(void) {
    // Configuration des broches PF2 et PF3 en sortie
    DDRF |= LED_MASK;

    while (1) {
        // Boucle de PWM logicielle (période de 100 * 30µs = 3 ms)
        for (uint8_t timer = 0; timer < 100; timer++) {
            if (timer < duty_cycle) {
                PORTF |= LED_MASK;   // Allumer les LEDs
            } else {
                PORTF &= ~LED_MASK;  // Éteindre les LEDs
            }
            _delay_us(30);
        }

        // Gestion de la variation du rapport cyclique toutes les 10 itérations
        repeat_count++;
        if (repeat_count >= 10) {
            repeat_count = 0;
            duty_cycle += direction;

            // Inversion de la direction aux extrémités (0 ou 99)
            if (duty_cycle >= 99 || duty_cycle == 0) {
                direction = -direction;
            }
        }
    }
}

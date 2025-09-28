#include "millis.h"

#include <avr/io.h>
#include <avr/interrupt.h>

static volatile uint32_t ms = 0;

ISR(TIMER0_COMPA_vect) {
    ms++;
}

// normal mode, prescaler 64, max value 249: exactly 1 interrupt per ms
void millis_init(void) {
    cli();
    TCCR0A = (1 << WGM01);
    TCCR0B = (1 << CS01) | (1 << CS00);
    TIMSK0 = (1 << OCIE0A);
    OCR0A = 249;
    sei();
}

uint32_t millis(void) {
    uint32_t ms_now;
    uint8_t sreg = SREG;

    cli();
    ms_now = ms;
    SREG = sreg;

    return ms_now;
}

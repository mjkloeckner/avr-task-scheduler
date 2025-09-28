#include "timer.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#define TIMER_CALLBACKS_MAX_CNT 1

typedef struct {
    uint8_t callbacks_cnt;
    void (*callbacks[TIMER_CALLBACKS_MAX_CNT])(void);
} timer_t;

static timer_t timer = {0};

ISR(TIMER0_COMPA_vect) {
    for(uint8_t i = 0; i < timer.callbacks_cnt; ++i) {
        timer.callbacks[i]();
    }
}

// normal mode, prescaler 64, max value 250 == exact 1 interrupt per ms
void timer_init(void) {
    cli();
    TCCR0A = (1 << WGM01) | (1 << COM0A0);
    TCCR0B = (1 << CS01) | (1 << CS00);
    TIMSK0 = (1 << OCIE0A);
    OCR0A = 250;
    sei();

    // timer_add_callback(&timer_increment_millis);
}

void timer_add_callback(void (*callback)(void)) {
    if (timer.callbacks_cnt == TIMER_CALLBACKS_MAX_CNT) {
        return;
    }

    timer.callbacks[timer.callbacks_cnt] = callback;
    timer.callbacks_cnt++;
}

#include <avr/io.h>

#include "millis.h"
#include "scheduler.h"

#define BTN_PIN   2
#define LED_1_PIN 3
#define LED_2_PIN 4
#define LED_3_PIN 5

void toggle_led_1(void) {
    PIND = (1 << LED_1_PIN);
}

void toggle_led_2(void) {
    PIND = (1 << LED_2_PIN);
}

void read_button(void) {
    uint8_t btn_pin_state = (PIND & (1<<BTN_PIN));

    if (!btn_pin_state) {
        PORTD |= (1<<LED_3_PIN);
    } else {
        PORTD &= ~(1<<LED_3_PIN);
    }
}

void setup(void) {
    DDRD = (DDRD | (1<<LED_1_PIN) | (1<<LED_2_PIN) | (1<<LED_3_PIN)) & ~(1<<BTN_PIN);
    PORTD |= (1<<BTN_PIN);

    millis_init();

    scheduler_append_task(&toggle_led_1, 1000);
    scheduler_append_task(&toggle_led_2, 500);
    scheduler_append_task(&read_button, 0);
}

int main(void) {
    setup();

    while(1) {
        scheduler_update(millis());
    }

    return 0;
}

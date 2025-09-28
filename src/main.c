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
    if (PIND & (1<<BTN_PIN)) {
        PORTD &= ~(1<<LED_3_PIN);
    } else {
        PORTD |= (1<<LED_3_PIN);
    }
}

task_t tasks[] = {
    { toggle_led_1, 1000 },
    { toggle_led_2, 500 },
    { read_button,  0 }
};

void io_setup(void) {
    DDRD = (DDRD | (1<<LED_1_PIN) | (1<<LED_2_PIN) | (1<<LED_3_PIN)) & ~(1<<BTN_PIN);
    PORTD |= (1<<BTN_PIN);
}

int main(void) {
    io_setup();
    millis_init();
    scheduler_init(tasks, sizeof(tasks)/sizeof(tasks[0]));

    while(1) {
        scheduler_update(millis());
    }

    return 0;
}

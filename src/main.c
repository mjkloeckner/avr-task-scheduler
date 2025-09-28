#include <avr/io.h>

#include "timer.h"
#include "scheduler.h"

#define LED_1_PIN  3
#define LED_2_PIN  4

void toggle_led_1(void) {
    PIND = (1 << LED_1_PIN);
}

void toggle_led_2(void) {
    PIND = (1 << LED_2_PIN);
}

void setup(void) {
    DDRD |= (1 << LED_1_PIN) | (1 << LED_2_PIN);

    scheduler_init(tasks, tasks_cnt);

    // scheduler_append_task(&toggle_led_1, 1000);
    // scheduler_append_task(&toggle_led_2, 500);

    timer_init();
    timer_add_callback(&scheduler_update);
}

int main(void) {
    setup();

    while(1) {
        ;;
    }

    return 0;
}

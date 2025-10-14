#include <avr/io.h>
#include <stddef.h>

#include "millis.h"
#include "scheduler.h"

#define BTN_A_PIN 2
#define BTN_B_PIN 3
#define LED_1_PIN 4
#define LED_2_PIN 5
#define LED_3_PIN 6
#define LED_4_PIN 7

void toggle_led_1(void);
void toggle_led_2(void);
void read_button_a(void);
void read_button_b(void);

typedef enum {
    TOGGLE_LED_1_ID,
    TOGGLE_LED_2_ID,
    READ_BTN_A_ID,
    READ_BTN_B_ID,
    TASKS_COUNT
} task_id_e;

task_t tasks[] = {
    //   on_update  period                id
    { toggle_led_1,   1000,  TOGGLE_LED_1_ID },
    { toggle_led_2,    500,  TOGGLE_LED_2_ID },
    { read_button_a,     0,    READ_BTN_A_ID },
    { read_button_b,     0,    READ_BTN_B_ID }
};

void io_setup(void) {
    // outputs
    DDRD |= (1<<LED_1_PIN) | (1<<LED_2_PIN) | (1<<LED_3_PIN) | (1<<LED_4_PIN);

    // inputs with internall pullup
    DDRD &= ~((1<<BTN_A_PIN) | (1<<BTN_B_PIN));
    PORTD |= (1<<BTN_A_PIN) | (1<<BTN_B_PIN);
}

int main(void) {
    io_setup();

    millis_init(&scheduler_update_tick);

    scheduler_init(tasks, sizeof(tasks)/sizeof(tasks[0]));

    while(1) {
        scheduler_update();
    }

    return 0;
}

void toggle_led_1(void) {
    PIND = (1 << LED_1_PIN);
}

void toggle_led_2(void) {
    PIND = (1 << LED_2_PIN);
}

void read_button_a(void) {
    if (PIND & (1<<BTN_A_PIN)) {
        PORTD &= ~(1<<LED_4_PIN);
        scheduler_set_task_period(READ_BTN_A_ID, 0);
    } else {
        PORTD |= (1<<LED_4_PIN);
        scheduler_set_task_period(READ_BTN_A_ID, 150);
    }
}

void read_button_b(void) {
    if (PIND & (1<<BTN_B_PIN)) {
        PORTD &= ~(1<<LED_3_PIN);
    } else {
        PORTD |= (1<<LED_3_PIN);
    }
}

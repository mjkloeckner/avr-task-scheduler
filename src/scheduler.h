#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct {
    void (*task_update)(void);
    uint16_t period;
    uint8_t task_id;
    uint16_t ticks;
} task_t;

void scheduler_init(task_t *tasks, uint8_t task_count);
void scheduler_update(uint32_t t_ms);
void scheduler_set_task_period(uint8_t task_id, uint16_t new_period);

#ifdef __cplusplus
}
#endif

#endif // _SCHEDULER_H_

#include "scheduler.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void (*task_update)(void);
    uint16_t update_interval;
    uint16_t ticks;
} task_t;

typedef struct {
    uint8_t task_cnt;
    task_t tasks[SCHEDULER_MAX_TASKS_CNT];
} scheduler_t;

static scheduler_t scheduler = {0};

void scheduler_init(void) {
    scheduler.task_cnt = 0;
}

// should be called exactly every ms
void scheduler_update(void) {
    for (uint8_t i = 0; i < scheduler.task_cnt; ++i) {
        if (scheduler.tasks[i].ticks > 0) {
            scheduler.tasks[i].ticks--;
            continue;
        }

        scheduler.tasks[i].ticks = scheduler.tasks[i].update_interval;
        scheduler.tasks[i].task_update();
    }
}

void scheduler_append_task(void (*update_func)(void), uint16_t update_interval) {
    scheduler.tasks[scheduler.task_cnt].task_update = update_func;
    scheduler.tasks[scheduler.task_cnt].update_interval = update_interval - 1;
    scheduler.task_cnt++;
}

#ifdef __cplusplus
}
#endif

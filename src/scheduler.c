#include "scheduler.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t task_cnt, update_cnt;
    task_t *tasks;
} scheduler_t;

static scheduler_t scheduler = {0};

void scheduler_init(task_t *tasks, uint8_t task_count) {
    scheduler.tasks = tasks;
    scheduler.task_cnt = task_count;
}

void scheduler_update_tick(void) {
    scheduler.update_cnt += (scheduler.update_cnt == 255 ? 0 : 1);
}

// update every 1 ms
void scheduler_update(void) {
    if (scheduler.update_cnt == 0) {
        return;
    }

    scheduler.update_cnt--;

    for (uint8_t i = 0; i < scheduler.task_cnt; ++i) {
        if (scheduler.tasks[i].ticks > 1) {
            scheduler.tasks[i].ticks--;
            continue;
        }

        scheduler.tasks[i].ticks = scheduler.tasks[i].period;
        scheduler.tasks[i].on_update();
    }
}

void scheduler_set_task_period(uint8_t task_id, uint16_t new_period) {
    for (uint8_t i = 0; i < scheduler.task_cnt; ++i) {
        if (scheduler.tasks[i].id == task_id) {
            scheduler.tasks[i].period = new_period;
            scheduler.tasks[i].ticks = new_period;
        }
    }
}

#ifdef __cplusplus
}
#endif

#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#define SCHEDULER_MAX_TASKS_CNT 10

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void scheduler_update(uint32_t t_ms);
void scheduler_append_task(void (*update_func)(void), uint16_t update_interval);

#ifdef __cplusplus
}
#endif

#endif // _SCHEDULER_H_

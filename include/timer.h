#ifndef _TIMER_H_
#define _TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void timer_init(void);
void timer_add_callback(void (*func_ptr)(void));

#ifdef __cplusplus
}
#endif

#endif // _TIMER_H_

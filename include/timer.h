#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>

void timer_init(void);
void timer_add_callback(void (*func_ptr)(void));

#endif // _TIMER_H_

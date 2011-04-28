#ifndef TIMER_H
#define TIMER_H

#define TIMER_TICK_HZ 20

#include <stdint.h>

typedef void (*timer_event_cb)(void* data);
typedef uint64_t timer_time_t;

typedef struct timer_event {
  timer_time_t   time;
  timer_event_cb callback;
  void          *data;
} timer_event_t;

timer_time_t   timer_getmillis();
timer_event_t* timer_schedule(timer_time_t time, timer_event_cb callback, void* data);
void           timer_init();
void           timer_postpone(timer_event_t *event, timer_time_t time);

#endif

/* vim: set ts=2 sts=2 sw=2 et ft=c tw=120: */

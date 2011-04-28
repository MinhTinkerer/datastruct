#include "timer.h"

#include "heap.h"
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

static heap_t timer_events;
static void   timer_tick();
static int    timer_event_compare(void *a, void *b);
static void*  timer_main(void*);
static pthread_t       timer_thread;
static pthread_mutex_t timer_mutex;

timer_time_t timer_getmillis() {
  struct timespec time_posix;
  timer_time_t    time;
  clock_gettime(CLOCK_REALTIME, &time_posix);
  time = time_posix.tv_sec * 1000 + time_posix.tv_nsec / 1000000;
  return time;
}

static int timer_event_compare(void *a, void *b) {
  timer_event_t *c = a;
  timer_event_t *d = b;
  return c->time > d->time ? 1 : c->time < d->time ? -1 : 0;
}

static void timer_tick() {
  timer_event_t *event;
  timer_time_t   time;

  pthread_mutex_lock(&timer_mutex);
  time = timer_getmillis();
  for (;;) {
    event = heap_peek(&timer_events);
    if (event == NULL || event->time > time) { break; }
    event = heap_pop(&timer_events);
    event->callback(event->data);
    free(event);
  }
  pthread_mutex_unlock(&timer_mutex);
}

timer_event_t* timer_schedule(timer_time_t time, timer_event_cb callback, void* data) {
  timer_event_t *event = malloc(sizeof(timer_event_t));
  event->time     = time;
  event->callback = callback;
  event->data     = data;
  pthread_mutex_lock(&timer_mutex);
  heap_insert(&timer_events, event);
  pthread_mutex_unlock(&timer_mutex);
  return event;
}

static void* timer_main(void* _) {
  struct timespec delay;
  delay.tv_sec  = 0;
  delay.tv_nsec = 1000000000/TIMER_TICK_HZ;
  for (;;) {
    nanosleep(&delay, NULL);
    timer_tick();
  }
}

void timer_init() {
  heap_init(&timer_events, &timer_event_compare);
  pthread_mutex_init(&timer_mutex, NULL);
  pthread_create(&timer_thread, NULL, &timer_main, NULL);
}

void timer_postpone(timer_event_t *event, timer_time_t time) {
  pthread_mutex_lock(&timer_mutex);
  event->time = time;
  int index = heap_index(&timer_events, event);
  heap_percolate_down(&timer_events, index);
  pthread_mutex_unlock(&timer_mutex);
}

/* vim: set ts=2 sts=2 sw=2 et ft=c tw=120: */

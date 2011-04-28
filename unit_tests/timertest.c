#include "timer.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TEST_MAX 0x1000

volatile int count = 0;

void event_callback(void* data) {
  timer_time_t *value = data;
  timer_time_t  time  = timer_getmillis();
  printf("\r%llu %llu", time, *value);
  if (abs(time - *value) > 100) {
    fprintf(stderr, "\nWrong time!\n");
    exit(-1);
  }
  free(data);
  count--;
}

int main() {
  timer_time_t *value;

  timer_init();
  srand(time(NULL));

  /* randomly insert events */
  printf("Inserting random events:\n");
  for (int i=0; i < TEST_MAX; i++) {
    value   = malloc(sizeof(timer_time_t));
    *value  = timer_getmillis();
    *value += rand() % 10000;
    *value += 3000;
    printf("\r%llu ", *value);
    timer_schedule(*value, &event_callback, value);
    count++;
  }
  printf("\nWaiting for events to complete. \n");
  while (count) {}
  printf("\nSuccess!\n");
  return 0;
}
/* vim: set ts=2 sts=2 sw=2 et ft=c tw=120: */

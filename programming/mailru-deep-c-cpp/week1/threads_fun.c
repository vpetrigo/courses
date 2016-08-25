#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *thread_routine(void *);

int main() {
  pthread_attr_t attr;
  pthread_t thread;

  pthread_attr_init(&attr);
  pthread_create(&thread, NULL, &thread_routine, NULL);
  pthread_join(thread, NULL);
  puts("Hello from Main()");

  return 0;
}

void *thread_routine(void *arg) {
  puts("Hello from a thread");
  
  return NULL;
}
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

struct ToCalculate {
  int *data;
  size_t size;
};

void *thread_routine(void *);

int main() {
  const size_t tasks_q = 2;
  const size_t NUM_THREADS = 2;
  printf("NUM THREADS: %zu\n", NUM_THREADS);
  pthread_t *threads_pool = malloc(NUM_THREADS * sizeof(pthread_t));
  int **res = malloc(2 * sizeof(int *));
  int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 10};
  int b[] = {100, 200, 300, 400, 500, 600, 700};

  struct ToCalculate data[2] = { 
    {.data = a, .size = COUNT_OF(a)}, 
    {.data = b, .size = COUNT_OF(b)}
  };

  for (size_t i = 0; i < tasks_q; ++i) {
    pthread_create(threads_pool + i, NULL, &thread_routine, data + i);
  }

  for (size_t i = 0; i < tasks_q; ++i) {
    pthread_join(*(threads_pool + i), (void **) &res[i]);
  }

  puts("Hello from Main()");
  printf("sum1: %d, sum2: %d\n", *res[0], *res[1]);
  for (size_t i = 0; i < tasks_q; ++i) {
    free(res[i]);
  }
  free(res);

  return 0;
}

void *thread_routine(void *arg) {
  puts("Hello from a thread");
  struct ToCalculate *s = (struct ToCalculate *) arg;
  printf("array size: %zu\n", s->size);
  int *sum = malloc(sizeof(int));

  for (size_t i = 0; i < s->size; ++i) {
    *sum += s->data[i];
  } 
  
  return sum;
}
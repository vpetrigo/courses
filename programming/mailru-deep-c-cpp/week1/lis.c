#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>

#define MIN_SEQ_SIZE 2

bool read_number(const char *fmt, void *num);
bool read_int64(int64_t *num);
bool read_double(double *num);
bool check_input(void);
void test_seq_size(int64_t n);
void test_seq_ptr(void *seq);
double *read_sequence(int64_t seq_size);
void print_sequence(double *seq, size_t size);

int main() {
  int64_t N = 0;
  double *sequence = NULL;

  if (read_int64(&N) && N > MIN_SEQ_SIZE &&
      (sequence = read_sequence(N)) != NULL) {
    test_seq_size(N);
    test_seq_ptr(sequence);
    print_sequence(sequence, N);
  }
  else {
    puts("[error]");
  }

  return 0;
}

bool read_number(const char *fmt, void *num) {
  // read number from the stdin and check whether we read
  // "true" number instead of a part of string literal
  // example: '4abc' for reading base 10 integer is a bad input
  //          '3.14' for plain integer is a bad input
  //          'asdf' for any number is a bad input
  if (scanf(fmt, num) != EOF && check_input()) {
    return true;
  }

  return false;
}

bool read_int64(int64_t *num) {
  const char *fmt = "%" SCNi64;

  return read_number(fmt, num);
}

bool read_double(double *num) {
  const char *fmt = "%lf";

  return read_number(fmt, num);
}

void test_seq_size(int64_t n) {
  assert(n > 0);
}

void test_seq_ptr(void *seq) {
  assert(seq != NULL);
}

bool check_input(void) {
  // for current problem it is necessary to check
  // input for trailing symbols after a number
  // example: 3.14 - wrong input
  //          3abc - wrong input
  return isspace(getchar());
}

double *read_sequence(int64_t seq_size) {
  double *sequence = malloc(seq_size * sizeof(double));

  if (sequence != NULL) {
    double number;

    for (size_t i = 0; i < seq_size; ++i) {
      if (read_double(&number)) {
        sequence[i] = number;
      }
      else {
        free(sequence);
        sequence = NULL;
        break;
      }
    }
  }

  return sequence;
}

void print_sequence(double *seq, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    printf("%lf", seq[i]);
    if (i != size - 1) {
      putchar(' ');
    }
  }
}

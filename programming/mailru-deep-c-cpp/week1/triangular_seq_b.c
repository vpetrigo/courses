#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <inttypes.h>
#include <errno.h>

uint64_t read_unsigned64(void);
bool is_same_numbers_repr(const char * __restrict, const char * __restrict);
size_t read_number_to_buffer(char * __restrict buf, size_t size);
size_t triang_sequence_pos(uint64_t number);

int main() {
  uint64_t num = read_unsigned64();
  
  if (num >= 1 && num <= INT64_MAX) {
    printf("%zu\n", triang_sequence_pos(num));
  }
  else {
    puts("0");
  }

  return 0;
}

#define BUFFER_SIZE 1024

uint64_t read_unsigned64(void) {
  char buffer[BUFFER_SIZE];
  size_t result = read_number_to_buffer(buffer, BUFFER_SIZE);
  uint64_t number = 0;

  if (result != 0 && buffer[0] != '-') {
    number = strtoull(buffer, NULL, 10);
  }
  char back_buffer[BUFFER_SIZE];

  sprintf(back_buffer, "%" PRIu64, number);

  if (!is_same_numbers_repr(buffer, back_buffer)) {
    number = 0;
  }

  return number;
}

bool is_same_numbers_repr(const char * __restrict num1, const char * __restrict num2) {
  if (*num1 == '+') {
    ++num1;
  }
  if (*num2 == '+') {
    ++num2;
  }

  return strcmp(num1, num2) == 0;
}

// Read a number from the stdin to a buffer
// return 0 if nothing was read or positive integer otherwise
size_t read_number_to_buffer(char * __restrict buf, size_t size) {
  assert(size != 0);
  char ch = '\0';
  size_t counter = 0;

  while ((ch = getchar()) != EOF && isspace(ch)) {
    // skip whitespaces
  }

  if (ch == '+' || ch == '-' || ch == '.' || isdigit(ch)) {
    *buf++ = ch;
    ++counter;
  }

  while (counter < size - 1 && (ch = getchar()) != EOF &&
         (isdigit(ch) || ch == '.')) {
    *buf++ = ch;
    ++counter;
  }

  *buf = '\0';
  
  if (ch != EOF && !isspace(ch)) {
    // string literal
    counter = 0;
  }

  return counter;
}

size_t triang_sequence_pos(uint64_t number) {
  uint64_t current = 1;
  uint64_t increment = 2;
  size_t pos = 1;

  while (current < number) {
    current += increment++;
    ++pos;
  }

  if (number != current) {
    pos = 0;
  }

  return pos;
}
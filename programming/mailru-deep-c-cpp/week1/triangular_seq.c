#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <inttypes.h>

#define NUMSTR_SIZE 1024

uint32_t is_triangseq(const uint_fast64_t number);
uint_fast64_t read_number(void);
uint_fast64_t convert_to_number(const char *num_repr, size_t size);

int main() {
  uint_fast64_t number = read_number();
  // we have to deal only with numbers from range [1, 9'223'372'036'854'775'807]
  if (number >= 1 && number <= INT64_MAX) {
    printf("%"PRIu32, is_triangseq(number));
  }
  else {
    puts("0");
  }

  return 0;
}

uint32_t is_triangseq(const uint_fast64_t number) {
  uint_fast64_t triangseq_num = 1;
  uint_fast64_t increment = 2;
  uint32_t position = 1;

  while (triangseq_num < number) {
    triangseq_num += increment++;
    ++position;
  }

  if (triangseq_num != number) {
    position = 0;
  }

  return position;
}

uint_fast64_t read_number(void) {
  // read number with intermediate string buffer
  char number_string[NUMSTR_SIZE];
  int result = scanf("%s", number_string);

  if (result != EOF) {
    // convert string to number
    return convert_to_number(number_string, NUMSTR_SIZE);
  }

  return 0U;
}

uint_fast64_t convert_to_number(const char *num_repr, size_t size) {
  uint_fast64_t number = 0;
  int result = sscanf(num_repr, "%"SCNuFAST64, &number);
  char back_conv_result[NUMSTR_SIZE];

  if (result != EOF) {
    sprintf(back_conv_result, "%"PRIuFAST64, number);
    if (strncmp(num_repr, back_conv_result, size) != 0 && *num_repr != '+') {
      // here we get if the number is exceeded the UINT64_MAX value
      // or it is negative
      number = 0;
    }
  }

  return number;
}

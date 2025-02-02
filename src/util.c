#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "sort.h"

#define PRINT_FORMAT(x) _Generic((x), \
  uint64_t: "%lu", \
  uint32_t: "%u", \
  uint16_t: "%hu", \
  uint8_t: "%hhu", \
  default: "UNKNOWN_TYPE" \
)

void print_element(sort_t x) {
  printf(PRINT_FORMAT(x), x);
}

void print_array(sort_t *a, size_t a_len) {
  for (size_t i = 0; i < a_len; ++i) {
    print_element(a[i]);
    printf(" ");
  }
  printf("\n");
}

void merge(sort_t *a, size_t a_len, sort_t *b, size_t b_len, sort_t *c) {
  size_t i = 0, j = 0, k = 0;
  while (i < a_len || j < b_len) {
    if (i != a_len && (j == b_len || a[i] < b[j])) {
      c[k++] = a[i++];
    } else {
      c[k++] = b[j++];
    }
  }
}

double get_time_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
}

bool is_sorted(sort_t *a, size_t a_len) {
  for (size_t i = 1; i < a_len; ++i) {
    if (a[i] < a[i-1]) {
      return false;
    }
  }
  return true;
}

void measure(const char *func_name, void (*func)(sort_t *, size_t), const sort_t *a, size_t a_len) {
  sort_t *a_copy = (sort_t *) malloc(a_len * sizeof(sort_t));
  memcpy(a_copy, a, a_len * sizeof(sort_t));

  double start_time = get_time_ms();
  func(a_copy, a_len);
  double end_time = get_time_ms();


  if (!is_sorted(a_copy, a_len)) {
    printf("Function %s failed to sort correctly\n", func_name);
    if (a_len < 20) {
      printf("Printing resulting array:\n");
      for (size_t i = 0; i < a_len; ++i) {
        print_element(a[i]);
        printf(" ");
      }
      printf("\n");
    }
    return;
  }

  printf("Function %s sorted the array in %f milliseconds\n", func_name, end_time-start_time);
  free(a_copy);
}



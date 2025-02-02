#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "sort.h"

void print_array(int *a, int a_len) {
  for (int i = 0; i < a_len; ++i) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

void merge(int *a, int a_len, int *b, int b_len, int *c) {
  int i = 0, j = 0, k = 0;
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

bool is_sorted(const int *a, int a_len) {
  for (int i = 1; i < a_len; ++i) {
    if (a[i] < a[i-1]) {
      return false;
    }
  }
  return true;
}

void measure(const char *func_name, void (*func)(int *, int), const int *a, int a_len) {
  int *a_copy = (int *) malloc(a_len * sizeof(int));
  memcpy(a_copy, a, a_len * sizeof(int));

  double start_time = get_time_ms();
  func(a_copy, a_len);
  double end_time = get_time_ms();


  if (!is_sorted(a_copy, a_len)) {
    printf("Function %s failed to sort correctly\n", func_name);
    if (a_len < 20) {
      printf("Printing resulting array:\n");
      for (int i = 0; i < a_len; ++i) {
        printf("%d ", a[i]);
      }
      printf("\n");
    }
    return;
  }

  printf("Function %s sorted the array in %f milliseconds\n", func_name, end_time-start_time);
  free(a_copy);
}



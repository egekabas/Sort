#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "sort.h"

void mergesort(int *a, int a_len) {
  if (a_len <= 15) {
    insertion_sort(a, a_len);
    return;
  }

  int left_len = a_len/2;
  int *left = a;

  int right_len = a_len-left_len;
  int *right = a + left_len;

  mergesort(left, left_len);
  mergesort(right, right_len);

  int *tmp = (int *)malloc(a_len * sizeof(int));
  merge(left, left_len, right, right_len, tmp);
  memcpy(a, tmp, a_len * sizeof(int));
  free(tmp);
}

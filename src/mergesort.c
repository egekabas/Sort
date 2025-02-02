#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "sort.h"

void mergesort(sort_t *a, size_t a_len) {
  if (a_len <= 15) {
    insertion_sort(a, a_len);
    return;
  }

  size_t left_len = a_len/2;
  sort_t *left = a;

  size_t right_len = a_len-left_len;
  sort_t *right = a + left_len;

  mergesort(left, left_len);
  mergesort(right, right_len);

  sort_t *tmp = (sort_t *)malloc(a_len * sizeof(sort_t));
  merge(left, left_len, right, right_len, tmp);
  memcpy(a, tmp, a_len * sizeof(sort_t));
  free(tmp);
}

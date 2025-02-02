#include "util.h"
#include "sort.h"

void insertion_sort(sort_t *a, size_t a_len) {
  for (size_t i = 1; i < a_len; ++i) {
    size_t j = i;
    while (j > 0 && a[j] < a[j-1]) {
      swap(a + j, a + j-1);
      j--;
    }
  }
}
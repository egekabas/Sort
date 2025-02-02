#include <stdlib.h>
#include "util.h"
#include "sort.h"

void quicksort(sort_t *a, size_t a_len) {
  if(a_len <= 15) {
    insertion_sort(a, a_len);
    return;
  }
  
  size_t pivot_idx = rand()%a_len;

  swap(a, a + pivot_idx);
  pivot_idx = 0;
  size_t pivot = a[pivot_idx];

  for (size_t i = 1; i < a_len; ++i) {
    if (a[i] < pivot) {
      swap(a + i, a + pivot_idx + 1);
      swap(a + pivot_idx, a + pivot_idx + 1);

      pivot_idx += 1;
    }
  }

  quicksort(a, pivot_idx);
  quicksort(a + pivot_idx + 1, a_len - (pivot_idx + 1));
}

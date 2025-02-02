#include "util.h"
#include "sort.h"

void insertion_sort(int *a, int a_len) {
  for (int i = 1; i < a_len; ++i) {
    int j = i;
    while (j > 0 && a[j] < a[j-1]) {
      swap(a + j, a + j-1);
      j--;
    }
  }
}
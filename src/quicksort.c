#include <stdlib.h>
#include "util.h"
#include "sort.h"

void quicksort(sort_t *a, size_t a_len) {
  size_t threshold = IS_DEBUG ? 1 : 15;

  if(a_len <= threshold) {
    insertion_sort(a, a_len);
    return;
  }

  IF_DEBUG(
    printf("Quicksort called with len %lu\n", a_len);  
    print_array(a, a_len);
  );
  
  sort_t pivot = a[rand() % a_len];
  size_t lt = 0, le = 0;
  
  for (size_t i = 0; i < a_len; ++i) {
    IF_DEBUG(
      printf("%lu %lu %lu\n", i, lt, le);
    );
    if (a[i] == pivot) {
      swap(a + i, a + le);
      le++;
    } else if (a[i] < pivot) {
      swap(a + i, a + le);
      swap(a + lt, a + le);
      ++lt;++le;
    }
  }

  IF_DEBUG(
    printf("Pivot: ");
    print_element(pivot);
    printf("\n");
    print_array(a, a_len);
  );


  quicksort(a, lt);
  quicksort(a + le, a_len - le);
}

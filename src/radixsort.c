#include <string.h>
#include <stdlib.h>

#include "util.h"
#include "sort.h"

void radixsort(sort_t *a, size_t a_len) {
  size_t bitcnt = sizeof(sort_t) * 8;
  sort_t *one_ar = (sort_t *)malloc(a_len * sizeof(sort_t));
  
  IF_DEBUG(
    printf("Array beforehand\n");
    print_array(a, a_len);
  );

  for (size_t bit = 0; bit < bitcnt; ++bit){
    size_t zero_len = 0;
    size_t one_len = 0;
    for (size_t i = 0; i < a_len; ++i) {
      if (a[i] & (1LL<<bit)) {
        one_ar[one_len++] = a[i];
      } else {
        a[zero_len++] = a[i];
      }
    }
    
    memcpy(a + zero_len, one_ar, one_len * sizeof(sort_t));

    IF_DEBUG(
      printf("After radix on bit %lu\n", bit);
      print_array(a, a_len);
    );
  }

  // free(one_ar);
}

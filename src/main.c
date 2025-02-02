#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "sort.h"

int compare(const void *a, const void *b) {
  sort_t x = *(sort_t *)a;
  sort_t y = *(sort_t *)b;
  
  return (x > y) - (x < y);
}

void library_sort(sort_t *a, size_t a_len) {
  qsort(a, a_len, sizeof(sort_t), compare);
}


int main(int argc, char *argv[]) {
  // srand(time(NULL));
  srand(3);

  if (argc != 2) {
    printf("Call with 1 argument: the array size\n");
    return 1;
  }

  size_t a_len = atoi(argv[1]);
  sort_t *a = (sort_t *)malloc(a_len * sizeof(sort_t));
  for (size_t i = 0; i < a_len; ++i) {
    a[i] = rand() % (a_len * 10);
    // a[i] = rand() % (4);
    
  }

  sort_t *a_sorted = (sort_t *)malloc(a_len * sizeof(sort_t));
  memcpy(a_sorted, a, a_len * sizeof(sort_t));

  library_sort(a_sorted, a_len);


  printf("Non-parallel algorithms: \n");
  measure("merge sort", mergesort, a, a_len, a_sorted);
  measure("quicksort", quicksort, a, a_len, a_sorted);
  measure("heapsort", heapsort, a, a_len, a_sorted);
  measure("radix sort", radixsort, a, a_len, a_sorted);

  printf("\nParallel algorithms: \n");
  measure("sample sort with qsort", sample_sort_with_qs, a, a_len, a_sorted);
  measure("sample sort with merge sort", sample_sort_with_mergesort, a, a_len, a_sorted);

  free(a);
}
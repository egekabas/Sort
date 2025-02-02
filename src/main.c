#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "util.h"
#include "sort.h"


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
  }

  printf("Non-parallel algorithms: \n");
  measure("merge sort", mergesort, a, a_len);
  measure("quicksort", quicksort, a, a_len);
  measure("heapsort", heapsort, a, a_len);

  printf("\nParallel algorithms: \n");
  measure("sample sort with qsort", sample_sort_with_qs, a, a_len);
  measure("sample sort with merge sort", sample_sort_with_mergesort, a, a_len);

  free(a);
}
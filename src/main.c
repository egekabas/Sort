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

  int a_len = atoi(argv[1]);
  int *a = (int *)malloc(a_len * sizeof(int));
  for (int i = 0; i < a_len; ++i) {
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
#ifndef SORT_H
#define SORT_H

void insertion_sort(int *a, int a_len);

void mergesort(int *a, int a_len);
void quicksort(int *a, int a_len);
void heapsort(int *a, int a_len);

void sample_sort(int *a, int a_len, void *(*sort) (void *));
void sample_sort_with_qs(int *a, int a_len);
void sample_sort_with_mergesort(int *a, int a_len);



#endif
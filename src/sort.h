#ifndef SORT_H
#define SORT_H

#include <stdint.h>
#include <stddef.h>

// only support unsigned integer types

typedef uint64_t sort_t;
// typedef uint32_t sort_t;
// typedef uint16_t sort_t;
// typedef uint8_t sort_t;

void insertion_sort(sort_t *a, size_t a_len);

void mergesort(sort_t *a, size_t a_len);
void quicksort(sort_t *a, size_t a_len);
void heapsort(sort_t *a, size_t a_len);

void radixsort(sort_t *a, size_t a_len);

void sample_sort(sort_t *a, size_t a_len, void *(*sort) (void *));
void sample_sort_with_qs(sort_t *a, size_t a_len);
void sample_sort_with_mergesort(sort_t *a, size_t a_len);

#endif
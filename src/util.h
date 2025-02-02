#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <stdio.h>

#include "sort.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

void print_element(sort_t x);
void print_array(sort_t *a, size_t a_len);

static inline void swap(sort_t *a, sort_t *b) {
  sort_t tmp = *a;
  *a = *b;
  *b = tmp;
}
void merge(sort_t *a, size_t a_len, sort_t *b, size_t b_len, sort_t *c);
double get_time_ms();
bool is_sorted(sort_t *a, size_t a_len);
bool array_same(sort_t *a, sort_t *b, size_t len);
void measure(const char *func_name, void (*func)(sort_t *, size_t), sort_t *a, size_t a_len, sort_t *sorted);

#ifdef DEBUG
  #define IF_DEBUG(x) \
    do { \
      x \
    } while (0)
  
  #define IS_DEBUG 1
#else
  #define IF_DEBUG(x) do {} while (0)
  #define IS_DEBUG 0
#endif

#endif
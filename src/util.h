#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>


void print_array(int *a, int a_len);
static inline void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
void merge(int *a, int a_len, int *b, int b_len, int *c);
double get_time_ms();
bool is_sorted(const int *a, int a_len);
void measure(const char *func_name, void (*func)(int *, int), const int *a, int a_len);

#endif
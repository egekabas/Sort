#include <pthread.h>
#include <stdlib.h>

#include "util.h"
#include "sort.h"


#define BUCKET_CNT 8

typedef struct {
  sort_t *a;
  size_t a_len;
} thread_job;

void *quicksort_for_thread(void *arg) {
  thread_job *typed_arg = (thread_job *) arg;
  quicksort(typed_arg->a, typed_arg->a_len);
  return NULL;
}

void *mergesort_for_thread(void *arg) {
  thread_job *typed_arg = (thread_job *) arg;
  mergesort(typed_arg->a, typed_arg->a_len);
  return NULL;
}

void sample_sort(sort_t *a, size_t a_len, void *(*sort) (void *)) {
  size_t threshold = IS_DEBUG ? 10 : 1000;
  if (a_len <  threshold) {
    quicksort(a, a_len);
    return;
  }

  //random samples
  sort_t samples[BUCKET_CNT-1];
  for (size_t i = 0; i < BUCKET_CNT-1; ++i) {
    samples[i] = a[rand() % a_len];
  }
  insertion_sort(samples, BUCKET_CNT-1);

  size_t bucket_beg[BUCKET_CNT-1];
  for (size_t i = 0; i < BUCKET_CNT-1; ++i) {
    bucket_beg[i] = 0;
  }

  IF_DEBUG(
    printf("Array: ");
    print_array(a, a_len);
    printf("Samples: ");
    print_array(samples, BUCKET_CNT-1);
  );

  for (size_t i = 0; i < a_len; ++i) {
    size_t cur_idx = i;
    for (size_t bucket = BUCKET_CNT - 2;;--bucket) {
      IF_DEBUG(
        print_element(a[cur_idx]);
        printf(" ");
        print_element(samples[bucket]);
        printf("\n");
      );
      if (a[cur_idx] >= samples[bucket]) {break;}
      swap(a + cur_idx, a + bucket_beg[bucket]);
      cur_idx = bucket_beg[bucket];
      bucket_beg[bucket] += 1;
      if (bucket == 0) {break;}
    }
  }

  IF_DEBUG(
    printf("Array after partitioning: ");
    print_array(a, a_len);
    printf("Buckets: ");
    for (size_t i = 0; i < BUCKET_CNT-1; ++i) {
      printf("%lu", i);
    }
    printf("\n");
  );

  thread_job jobs[BUCKET_CNT];
  size_t cur_beg = 0;
  for (size_t i = 0; i < BUCKET_CNT-1; ++i) {
    jobs[i].a = a + cur_beg;
    jobs[i].a_len = bucket_beg[i] - cur_beg;

    cur_beg = bucket_beg[i];
  }
  jobs[BUCKET_CNT-1].a = a + cur_beg;
  jobs[BUCKET_CNT-1].a_len = a_len - cur_beg;
  
  
  pthread_t threads[BUCKET_CNT-1];
  for (size_t i = 0; i < BUCKET_CNT-1; ++i) {
    pthread_create(&threads[i], NULL, sort, &jobs[i]);
  }
  sort(&jobs[BUCKET_CNT-1]);

  for (size_t i = 0; i < BUCKET_CNT-1; ++i) {
    pthread_join(threads[i], NULL);
  }
}

void sample_sort_with_qs(sort_t *a, size_t a_len) {
  return sample_sort(a, a_len, quicksort_for_thread);
}
void sample_sort_with_mergesort(sort_t *a, size_t a_len) {
  return sample_sort(a, a_len, mergesort_for_thread);
}

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
  if (a_len < 100) {
    quicksort(a, a_len);
    return;
  }
  
  //sample random idx
  size_t sample_idx[BUCKET_CNT-1];
  for (size_t i = 0; i < BUCKET_CNT - 1; ++i) {
    while (true){
      sample_idx[i] = rand()%a_len;
      bool same = false;
      for (size_t j = 0; j < i; ++j) {
        same |= sample_idx[j] == sample_idx[i];
      }
      if(!same) {break;}
    }
  }

  //sort random idx based on value in a
  for (size_t i = 1; i < BUCKET_CNT-1; ++i) {
    size_t j = i;
    while (j > 0 && a[sample_idx[j]] < a[sample_idx[j-1]]) {
      // swap(sample_idx + j, sample_idx + j - 1);

      size_t tmp = sample_idx[j];
      sample_idx[j] = sample_idx[j-1];
      sample_idx[j-1] = tmp;
      

      --j;
    }
  }

  //swap so values in the random idx come to the beginning
  for (size_t i = 0; i < BUCKET_CNT - 1; ++i) {
    swap(a + i, a + sample_idx[i]);
    for (size_t j = i+1; j < BUCKET_CNT - 1; ++j) {
      if (sample_idx[j] == i) {
        sample_idx[j] = sample_idx[i];
      }
    }
  }

  size_t bucket_beg[BUCKET_CNT-1];
  for (size_t i = 0; i < BUCKET_CNT-1; ++i) {
    bucket_beg[i] = i;
  }

  // divide into the buckets
  for (size_t i = BUCKET_CNT - 1; i < a_len; ++i) {
    size_t cur_idx = i;
    
    for (size_t bucket = BUCKET_CNT - 2;; --bucket) {
      if (a[cur_idx] >= a[bucket_beg[bucket]]) {break;}

      swap(a + cur_idx, a + bucket_beg[bucket] + 1);
      swap(a + bucket_beg[bucket], a + bucket_beg[bucket] + 1);

      cur_idx = bucket_beg[bucket];
      bucket_beg[bucket] += 1;

      if (bucket == 0){break;}
    }
  }

  thread_job jobs[BUCKET_CNT];
  size_t cur_beg = 0;
  for (size_t i = 0; i < BUCKET_CNT-1; ++i) {
    jobs[i].a = a + cur_beg;
    jobs[i].a_len = bucket_beg[i] - cur_beg;

    cur_beg = bucket_beg[i];
  }
  jobs[BUCKET_CNT-1].a = a + cur_beg;
  jobs[BUCKET_CNT-1].a_len = a_len - cur_beg;
  
  
  pthread_t threads[BUCKET_CNT];
  for (size_t i = 0; i < BUCKET_CNT; ++i) {
    pthread_create(&threads[i], NULL, sort, &jobs[i]);
  }
  for (size_t i = 0; i < BUCKET_CNT; ++i) {
    pthread_join(threads[i], NULL);
  }
}

void sample_sort_with_qs(sort_t *a, size_t a_len) {
  return sample_sort(a, a_len, quicksort_for_thread);
}
void sample_sort_with_mergesort(sort_t *a, size_t a_len) {
  return sample_sort(a, a_len, mergesort_for_thread);
}

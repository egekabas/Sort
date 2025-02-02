#include <pthread.h>
#include <stdlib.h>

#include "util.h"
#include "sort.h"


#define BUCKET_CNT 8

typedef struct {
  int *a;
  int a_len;
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

void sample_sort(int *a, int a_len, void *(*sort) (void *)) {
  if (a_len < 100) {
    quicksort(a, a_len);
    return;
  }
  
  //sample random idx
  int sample_idx[BUCKET_CNT-1];
  for (int i = 0; i < BUCKET_CNT - 1; ++i) {
    while (true){
      sample_idx[i] = rand()%a_len;
      bool same = false;
      for (int j = 0; j < i; ++j) {
        same |= sample_idx[j] == sample_idx[i];
      }
      if(!same) {break;}
    }
  }

  //sort random idx based on value in a
  for (int i = 1; i < BUCKET_CNT-1; ++i) {
    int j = i;
    while (j > 0 && a[sample_idx[j]] < a[sample_idx[j-1]]) {
      swap(sample_idx + j, sample_idx + j - 1);
      --j;
    }
  }

  //swap so values in the random idx come to the beginning
  for (int i = 0; i < BUCKET_CNT - 1; ++i) {
    swap(a + i, a + sample_idx[i]);
    for (int j = i+1; j < BUCKET_CNT - 1; ++j) {
      if (sample_idx[j] == i) {
        sample_idx[j] = sample_idx[i];
      }
    }
  }

  int bucket_beg[BUCKET_CNT-1];
  for (int i = 0; i < BUCKET_CNT-1; ++i) {
    bucket_beg[i] = i;
  }

  // divide into the buckets
  for (int i = BUCKET_CNT - 1; i < a_len; ++i) {
    int cur_idx = i;
    
    for (int bucket = BUCKET_CNT - 2; bucket >= 0; --bucket) {
      if (a[cur_idx] >= a[bucket_beg[bucket]]) {break;}

      swap(a + cur_idx, a + bucket_beg[bucket] + 1);
      swap(a + bucket_beg[bucket], a + bucket_beg[bucket] + 1);

      cur_idx = bucket_beg[bucket];
      bucket_beg[bucket] += 1;
    }
  }

  thread_job jobs[BUCKET_CNT];
  int cur_beg = 0;
  for (int i = 0; i < BUCKET_CNT-1; ++i) {
    jobs[i].a = a + cur_beg;
    jobs[i].a_len = bucket_beg[i] - cur_beg;

    cur_beg = bucket_beg[i];
  }
  jobs[BUCKET_CNT-1].a = a + cur_beg;
  jobs[BUCKET_CNT-1].a_len = a_len - cur_beg;
  
  
  pthread_t threads[BUCKET_CNT];
  for (int i = 0; i < BUCKET_CNT; ++i) {
    pthread_create(&threads[i], NULL, sort, &jobs[i]);
  }
  for (int i = 0; i < BUCKET_CNT; ++i) {
    pthread_join(threads[i], NULL);
  }
}

void sample_sort_with_qs(int *a, int a_len) {
  return sample_sort(a, a_len, quicksort_for_thread);
}
void sample_sort_with_mergesort(int *a, int a_len) {
  return sample_sort(a, a_len, mergesort_for_thread);
}

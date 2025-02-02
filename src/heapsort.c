#include "util.h"
#include "sort.h"


static void heapify_end(int *heap, int heap_len) {
  int node = heap_len-1;
  while (node > 0 && heap[node] > heap[(node-1)/2]) {
    swap(heap + node, heap + (node-1)/2);
    node = (node-1)/2;
  }
}

static void heapify_beg(int *heap, int heap_len) {
  int node = 0;
  while (node < heap_len) {
    int left = node * 2 + 1;
    int right = node * 2 + 2;

    if (left < heap_len && heap[left] > heap[node] && (right >= heap_len || heap[left] >= heap[right])) {
      swap(heap + node, heap + left);
      node = left;
    } else if(right < heap_len && heap[right] > heap[node]) {
      swap(heap + node, heap + right);
      node = right;
    } else {
      break;
    }      
  }
}

void heapsort(int *a, int a_len) {
  if(a_len <= 1) {
    insertion_sort(a, a_len);
    return;
  }

  for (int i = 1; i < a_len; ++i) {
    heapify_end(a, i + 1);
  }

  int cur_sorted = 0;
  while (cur_sorted < a_len) {
    swap(a, a + a_len - 1 - cur_sorted);
    cur_sorted++;
    heapify_beg(a, a_len-cur_sorted);
  }
}
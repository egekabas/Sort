// #include <pthread.h>
// #include <stdbool.h>
// #include <stdlib.h>
// #include "thread_pool.h"

// typedef struct {
//     void (*function)(void *); // Task function pointer
//     void *arg;                // Task argument
// } Task;

// typedef struct {
//   size_t thread_cnt;
//   pthread_t *threads;

//   size_t max_queue;
//   size_t queue_len;
//   Task *task_queue;
//   size_t head;
//   size_t tail;

//   pthread_mutex_t lock;
//   pthread_cond_t notify;
// } ThreadPool;

// static void *worker(void *arg) {
//   ThreadPool *pool = (ThreadPool *)(arg);
//   while(1) {
//     pthread_mutex_lock(&pool->lock);
//     while (pool->queue_len == 0) {
//       pthread_cond_wait(&pool->notify, &pool->lock);
//     }

//     Task task = pool->task_queue[pool->head++];
//     if(pool->head == pool->max_queue) {
//       pool->head = 0;
//     }
//     pool->queue_len--;

//     pthread_mutex_unlock(&pool->lock);
//     task.function(task.arg);
//   }
// }




// ThreadPool *init_threadpool(size_t thread_cnt, size_t max_queue) {
//   ThreadPool *pool = (ThreadPool *)malloc(sizeof(ThreadPool));
//   pool->thread_cnt = thread_cnt;
//   pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * thread_cnt);

//   pool->max_queue = max_queue;
//   pool->queue_len = 0;
//   pool->task_queue = (Task *)malloc(sizeof(Task) * max_queue);
//   pool->head = 0;
//   pool->tail = 0;

//   pthread_mutex_init(&pool->lock, NULL);
//   pthread_cond_init(&pool->notify, NULL);

//   for (size_t i = 0; i < pool->thread_cnt; ++i) {
//     pthread_create(&pool->threads[i], NULL, worker, NULL);
//   }
// }


// void destroy_threadpool(ThreadPool *pool) {
//   for (size_t i = 0; i < pool->thread_cnt; ++i) {
//     pthread_join(pool->threads[i], NULL);
//   }
//   free(pool->threads);
//   free(pool);
// }





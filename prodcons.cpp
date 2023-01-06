#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>


#define NUM_THREADS 6
#define MAX_COUNT 15

int count = 0;
int thread_ids[6] = {0,1,2,3,4,5};
pthread_mutex_t mutex;

sem_t full, empty;

// Producer function that generates 6 producer threads and places into a bucket
void* producer(void* arg)
{
   int i;
   for (i=0; i<MAX_COUNT; i++) {
       // Producer produces an item and places it into the buffer
       sem_wait(&empty);
       pthread_mutex_lock(&mutex);
       count++;
       printf("producer count = %d\n", count);
       pthread_mutex_unlock(&mutex);
       sem_post(&full);
   }
   printf("producer done\n");
   pthread_exit(NULL);
}

// Consumer function which consumes threads from bucket
void* consumer(void* arg)
{
   int id;
   int i;
   for (i=0; i<MAX_COUNT; i++) {
       // Consumer consumes an item from the buffer
       sem_wait(&full);
       pthread_mutex_lock(&mutex);
       count--;
       printf("consumer %d count = %d\n", id, count);
       pthread_mutex_unlock(&mutex);
       sem_post(&empty);
   }
   printf("consumer %d done\n", id);
   pthread_exit(NULL);
}

int main()
{
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   sem_init(&full, 0, 0);
   sem_init(&empty, 0, MAX_COUNT);
   pthread_mutex_init(&mutex, NULL);

   for(t=0;t<NUM_THREADS;t++) {
       if (t == 0) {
           printf("In main: creating producer thread %ld\n", t);
           rc = pthread_create(&threads[t], NULL, producer, (void *)&t);
       } else {
           printf("In main: creating consumer thread %ld\n", t);
           rc = pthread_create(&threads[t], NULL, consumer, (void *)&thread_ids[t]);
       }
       if (rc) {
           printf("ERROR; return code from pthread_create() is %d\n", rc);
           exit(-1);
       }
   }

   for(t=0;t<NUM_THREADS;t++) {
       pthread_join(threads[t], NULL);
   }

   printf("Main completed\n");
   sem_destroy(&full);
   sem_destroy(&empty);
   pthread_mutex_destroy(&mutex);
   pthread_exit(NULL);
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0;
int producing=30;
int consuming=30;

sem_t empty;
sem_t full;
sem_t mutex;

void* producer(void* arg) {
    int item;
    while (producing>0) {
        item = rand() % 100; // Produce an item 0 to 99
        sem_wait(&empty);
        sem_wait(&mutex);
        // Add the item to the buffer
        buffer[count++] = item;
        printf("Produced: %d\n", item);
        producing--;
        sem_post(&mutex);
        sem_post(&full);
    }
}

void* consumer(void* arg) {
    int item;
    while (consuming>0) {
        sem_wait(&full);
        sem_wait(&mutex);

        // Remove the item from the buffer
        item = buffer[--count];
        printf("Consumed: %d\n", item);
        consuming--;
        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
     sem_init(&mutex, 0, 1);
    

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
 
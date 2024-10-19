#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0;
int producing=30;
int consuming=30;



void* producer(void* arg) {
    int item;
    while (producing>0) {
        item = rand() % 100; // Produce an item 0 to 99
        
        // Add the item to the buffer
        buffer[count++] = item;
        printf("Produced: %d\n", item);
        producing--;
        
    }
}

void* consumer(void* arg) {
    int item;
    while (consuming>0) {
        

        // Remove the item from the buffer
        item = buffer[--count];
        printf("Consumed: %d\n", item);
        consuming--;
       
    }
}

int main() {
    pthread_t prod, cons;

   
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

   

    return 0;
}


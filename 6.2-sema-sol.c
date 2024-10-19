#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_ITERATIONS 10000

int count = 10;
sem_t semaphore; // semaphore object

// Critical section function
void critical_section(int process) {
    if(process==0){

        for (int i = 0; i < NUM_ITERATIONS; i++)
        count--;
    }
    else
    {
        for (int i = 0; i < NUM_ITERATIONS; i++)
        count++;
    }
}

// Function for process 0
void *process0(void *arg) {
    
        sem_wait(&semaphore); // Wait (decrement semaphore)
        critical_section(0);
        sem_post(&semaphore); // Signal (increment semaphore)
    
    return NULL;
}

// Function for process 1
void *process1(void *arg) {
    
        sem_wait(&semaphore); // Wait (decrement semaphore)
        critical_section(1);
        sem_post(&semaphore); // Signal (increment semaphore)
    
    return NULL;
}

int main() {
    pthread_t thread0, thread1;

    // Initialize semaphore
    sem_init(&semaphore, 0, 1);

    // Create threads
    pthread_create(&thread0, NULL, process0, NULL);
    pthread_create(&thread1, NULL, process1, NULL);

    // Wait for threads to finish
    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);

    // Destroy semaphore
    sem_destroy(&semaphore);

    printf("Final count: %d\n", count);

    return 0;
}


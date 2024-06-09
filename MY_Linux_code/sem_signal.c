#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_ITEMS 10

sem_t semaphore;

void* producer(void* arg) {
    for (int i = 0; i < MAX_ITEMS; ++i) {
        // Produce an item
        printf("Producer: Produced item %d\n", i);
        sem_post(&semaphore);  // Signal that an item is available
        sleep(1);  // Simulate time taken to produce an item
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < MAX_ITEMS; ++i) {
        sem_wait(&semaphore);  // Wait for an item to be available
        // Consume the item
        printf("Consumer: Consumed item %d\n", i);
        sleep(2);  // Simulate time taken to consume an item
    }
    return NULL;
}

int main() {
    pthread_t producerThread, consumerThread;

    sem_init(&semaphore, 0, 0);  // Initialize the semaphore with a count of 0

    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    sem_destroy(&semaphore);
    return 0;
}


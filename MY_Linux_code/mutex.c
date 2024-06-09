#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int shared_resource = 0;
pthread_mutex_t lock;
void* increment_resource(void* arg) {
    for (int i = 0; i < 1000000; ++i) {
        // Lock the mutex before accessing the shared resource
        pthread_mutex_lock(&lock);

        // Access or modify the shared resource
        shared_resource++;

        // Unlock the mutex after accessing the shared resource
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}
int main() {
    pthread_t threads[2];

    // Initialize the mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex initialization failed\n");
        return 1;
    }

    // Create threads
    for (int i = 0; i < 2; ++i) {
        if (pthread_create(&threads[i], NULL, increment_resource, NULL) != 0) {
            printf("Thread creation failed\n");
            return 1;
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < 2; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    // Print the result
    printf("Final value of shared_resource: %d\n", shared_resource);
    return 0;
}


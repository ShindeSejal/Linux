#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 3

void *thread_function(void *thread_id) {
    long tid;
    tid = (long)thread_id;

    printf("Thread %ld is executing...\n", tid);

    // Simulate some work by sleeping for a random duration (1 to 3 seconds)
    int sleep_duration = 1 + (rand() % 3);
    sleep(sleep_duration);

    printf("Thread %ld completed execution.\n", tid);

    // Exit the thread
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    // Create threads
    for (t = 0; t < NUM_THREADS; t++) {
        printf("Creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, thread_function, (void *)t);
        if (rc) {
            printf("Error: unable to create thread, %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }

    // Join and detach threads
    for (t = 0; t < NUM_THREADS; t++) {
        // Join the first thread
        if (t == 0) {
            printf("Joining thread %ld\n", t);
            rc = pthread_join(threads[t], NULL);
            if (rc) {
                printf("Error: unable to join thread, %d\n", rc);
                exit(EXIT_FAILURE);
            }
        } 
        // Detach the other threads
        else {
            printf("Detaching thread %ld\n", t);
            rc = pthread_detach(threads[t]);
            if (rc) {
                printf("Error: unable to detach thread, %d\n", rc);
                exit(EXIT_FAILURE);
            }
        }
    }

    printf("Thread 0 has been joined, and other threads have been detached.\n");

    // Exit the main thread
    pthread_exit(NULL);

    return 0;
}


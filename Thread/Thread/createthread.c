#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 4  // Adjust this value for the desired number of threads

void *thread_function(void *arg) {
    int thread_id = *(int *)arg;
    printf("Thread %d: Running...\n", thread_id);

    // Simulate some work by sleeping for 1 second
    sleep(1);

    printf("Thread %d: Finished.\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0) {
            perror("pthread_create failed");
            return 1;
        }
    }

    // Join created threads (wait for them to finish)
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join failed");
        }
    }

    printf("All threads finished.\n");
    return 0;
}


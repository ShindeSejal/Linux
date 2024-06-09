#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

#define NUM_THREADS 4 // Number of threads to create

void* thread_function(void* arg) {
    int core_id = *(int*)arg;
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    pthread_t thread = pthread_self();
    int s = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
    if (s != 0) {
        perror("pthread_setaffinity_np");
    }

    // Confirm CPU affinity setting
    CPU_ZERO(&cpuset);
    s = pthread_getaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
    if (s != 0) {
        perror("pthread_getaffinity_np");
    }

    if (CPU_ISSET(core_id, &cpuset)) {
        printf("Thread %d is running on CPU %d\n", core_id, core_id);
    } else {
        printf("Thread %d is not running on the expected CPU %d\n", core_id, core_id);
    }

    // Simulate work
    for (int i = 0; i < 1000000000; i++);
    while(1);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int core_ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        core_ids[i] = i;
        int rc = pthread_create(&threads[i], NULL, thread_function, &core_ids[i]);
        if (rc) {
            printf("Error:unable to create thread, %d\n", rc);
            exit(-1);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
	while(1);
    return 0;
}


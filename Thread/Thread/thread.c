# include <stdio.h>
#include <stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define NUM_THREADS 4

void *thread_function(void*thread_id){
	long tid;
	tid = (long)thread_id;

	printf("Thread %ld is executing \n",tid);

 // Simulate some work by sleeping for a random duration (1 to 3 seconds)
    int sleep_duration = 1 + (rand() % 3);
    sleep(sleep_duration);

    printf("Thread %ld completed execution.\n", tid);

    // Exit the thread
    pthread_exit(NULL);
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
     // Detach threads (optional, but recommended for background processes)
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_detach(threads[i]) != 0) {
            perror("pthread_detach failed");
        }
    }
      // Fork the process to run in the background (Linux-specific)
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process: Execute threads and exit
        printf("Child process (PID: %d) running threads...\n", getpid());
        for (int i = 0; i < NUM_THREADS; i++) {
            pthread_join(threads[i], NULL);
        }
        printf("Child process exiting.\n");
        exit(0);
    } else {
        // Parent process: Print confirmation and continue execution
        printf("Parent process (PID: %d) launched child process (PID: %d).\n", getpid(), pid);
    }

    // Run ps -eLf to observe threads (replace with your desired command)
    system("ps -eLf | grep background_process_name"); // Adjust for actual process name

    return 0;
}

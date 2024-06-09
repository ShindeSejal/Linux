#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_KEY 0x1234
#define NUM_INCREMENTS 100000

int main() {
    int shmid;
    int *shared_counter;

    // Create shared memory segment
    shmid = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory segment to the process's address space
    shared_counter = (int *)shmat(shmid, NULL, 0);
    if (shared_counter == (int *)-1) {
        perror("shmat");
        exit(1);
    }

    // Initialize shared counter
    *shared_counter = 0;

    // Fork process to create a child
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        for (int i = 0; i < NUM_INCREMENTS; i++) {
            int temp = *shared_counter;
            usleep(1);  // Small delay to increase likelihood of race condition
            *shared_counter = temp + 1;
        }
        shmdt(shared_counter); // Detach shared memory
        exit(0);
    } else {
        // Parent process
        for (int i = 0; i < NUM_INCREMENTS; i++) {
            int temp = *shared_counter;
            //usleep(1);  // Small delay to increase likelihood of race condition
            *shared_counter = temp + 1;
        }

        // Wait for child process to finish
        wait(NULL);

        printf("Final counter value: %d\n", *shared_counter);

        // Detach and remove shared memory
        shmdt(shared_counter);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}


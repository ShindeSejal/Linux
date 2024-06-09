#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_KEY 0x1234
#define SEM_KEY 0x5678
#define NUM_INCREMENTS 100000

// Semaphore operation structures
struct sembuf p = {0, -1, SEM_UNDO}; // Wait (P)
struct sembuf v = {0, 1, SEM_UNDO};  // Signal (V)

int main() {
    int shmid, semid;
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

    // Create semaphore
    semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (semid < 0) {
        perror("semget");
        exit(1);
    }

    // Initialize semaphore to 1
    semctl(semid, 0, SETVAL, 1);

    // Fork process to create a child
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        for (int i = 0; i < NUM_INCREMENTS; i++) {
            semop(semid, &p, 1); // Wait (P)
            (*shared_counter)++;
            semop(semid, &v, 1); // Signal (V)
        }
        shmdt(shared_counter); // Detach shared memory
        exit(0);
    } else {
        // Parent process
        for (int i = 0; i < NUM_INCREMENTS; i++) {
            semop(semid, &p, 1); // Wait (P)
            (*shared_counter)++;
            semop(semid, &v, 1); // Signal (V)
        }

        // Wait for child process to finish
        wait(NULL);

        printf("Final counter value: %d\n", *shared_counter);

        // Detach and remove shared memory and semaphore
        shmdt(shared_counter);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID);
    }

    return 0;
}


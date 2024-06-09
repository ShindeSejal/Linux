#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include <errno.h>
#include <string.h>

// Function to fetch the number of CPU cores available
int get_cpu_cores() {
    return sysconf(_SC_NPROCESSORS_ONLN);
}

// Function to set CPU affinity for a process
void set_cpu_affinity(pid_t pid, int core_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    if (sched_setaffinity(pid, sizeof(cpu_set_t), &cpuset) == -1) {
        fprintf(stderr, "Error setting CPU affinity: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

int main() {
    int num_cores = get_cpu_cores();
    printf("Number of CPU cores available: %d\n", num_cores);

    if (num_cores < 2) {
        fprintf(stderr, "At least 2 CPU cores are required for this program.\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid;
    for (int i = 0; i < num_cores; i++) {
        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Fork failed: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            set_cpu_affinity(getpid(), i);

            char *task;
            if (i % 2 == 0) {
                task = "/bin/ls"; // Example task 1
            } else {
                task = "/bin/pwd"; // Example task 2
            }

            // Use execl to replace the process image
            execl(task, task, (char *)NULL);

            // If execl fails
            fprintf(stderr, "Execl failed: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        // Parent process continues to create more children
    }

    // Wait for all child processes to complete
    for (int i = 0; i < num_cores; i++) {
        wait(NULL);
    }

    return 0;
}

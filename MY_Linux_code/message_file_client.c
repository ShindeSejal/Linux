#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define QUEUE_NAME  "/test_queue"
#define MAX_SIZE    1024
#define MSG_STOP    "exit"

int main() {
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_SIZE + 1];
    ssize_t bytes_read;
    int fd;

    // Wait briefly to ensure the server has created the message queue
    sleep(1);

    // Open the message queue
    mq = mq_open(QUEUE_NAME, O_RDONLY);
    if (mq == (mqd_t) -1) {
        perror("mq_open");
        exit(1);
    }

    // Get message queue attributes
    if (mq_getattr(mq, &attr) == -1) {
        perror("mq_getattr");
        exit(1);
    }

    // Open the file for writing
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Receive the data from the message queue and write it to the file
    while (1) {
        bytes_read = mq_receive(mq, buffer, attr.mq_msgsize, NULL);
        if (bytes_read == -1) {
            perror("mq_receive");
            exit(1);
        }

        buffer[bytes_read] = '\0';

        if (strcmp(buffer, MSG_STOP) == 0) {
            break;
        }

        if (write(fd, buffer, bytes_read) == -1) {
            perror("write");
            exit(1);
        }
    }

    // Cleanup
    close(fd);
    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    return 0;
}


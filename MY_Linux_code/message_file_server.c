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
    char buffer[MAX_SIZE];
    int fd;
    ssize_t bytes_read;

    // Initialize the message queue attributes
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    // Create the message queue
    mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY | O_EXCL, 0644, &attr);
    if (mq == (mqd_t) -1) {
        perror("mq_open");
        exit(1);
    }

    // Open the file
    fd = open("data.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Read from the file and send the data to the message queue
    while ((bytes_read = read(fd, buffer, MAX_SIZE)) > 0) {
        if (mq_send(mq, buffer, bytes_read, 0) == -1) {
            perror("mq_send");
            exit(1);
        }
    }

    // Send stop message
    if (mq_send(mq, MSG_STOP, strlen(MSG_STOP) + 1, 0) == -1) {
        perror("mq_send");
        exit(1);
    }

    // Cleanup
    close(fd);
    mq_close(mq);

    return 0;
}


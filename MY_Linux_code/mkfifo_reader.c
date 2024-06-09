#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char *fifo = "/tmp/my_named_pipe";
    char buffer[100];
    while(1)
    {
    	fd = open(fifo, O_RDONLY);
    	read(fd, buffer, sizeof(buffer));
   	printf("Received: %s\n", buffer);
    	close(fd);
    }


    return 0;
}


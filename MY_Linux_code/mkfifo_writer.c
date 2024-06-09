#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd;
    char *fifo = "/tmp/my_named_pipe";
    char buff[100],buff2[100];

    mkfifo(fifo, 0666);
    while(1)
    {
    	fd = open(fifo, O_WRONLY);
	fgets(buff2,100,stdin);
    	write(fd, buff2, strlen(buff2) + 1);

	close(fd);

/*	fd = open(fifo,O_RDONLY);

	read(fd, buff,sizeof(buff));

	printf("User 2 : S\n",buff);
    
    	close(fd);*/
    }

    return 0;
}


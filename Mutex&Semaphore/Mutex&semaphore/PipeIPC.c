/*Write a code for implementation of the PIPE IPC and write the complete working of it.*/

#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>            
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){

	int fd[2];
	// fd[0] ---> read
	// fd[1] ---> write
	char buff[150];
	int ret;

	if(pipe(fd) == -1){
		printf("error in opening the pipe\n");
		return -1;
	}

	else{
		ret = fork(); //create fork

	if(ret<0){
		printf("Not able to create the process");
		return 1;
	}

	if(ret == 0){
	//while writing you need to close the read file descriptor
	close(fd[0]);
	printf("Enter the data in string: \n");
	scanf("%[^\n]s",buff);
	if(write(fd[1],&buff,strlen(buff)) == -1){
		printf("Not able write the content in file\n");
	}
	close(fd[1]);
	return 0;

	}

	if(ret > 0){

	wait(NULL);
	close(fd[1]);
	if(read(fd[0],&buff,sizeof(buff)) == -1){
		printf("Not able to read from parent process\n");
	}

else{
	//close(fd[0]);
	printf("%s\n",buff);
	close(fd[0]);
}
printf("\n %s Got from Parent Process\n",buff);
return 0;

}

}
return 0;
}



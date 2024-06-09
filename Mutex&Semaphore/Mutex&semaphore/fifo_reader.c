#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(){

	int arr[2];
	while(1){
	int fd = open("sum",O_RDONLY);
	if (fd == -1){
		return -1;
	}

	for(int i=0; i<2; i++){
	if(read(fd, &arr[i], sizeof(arr))==-1){
			return -1;
		}

		close(fd);

	       int sum = 0;
	       for(int i=0; i<2; i++){
	       	sum += arr[i];
	       }	

		printf("Received %d\n",sum);
	}

}
	return 0;
}


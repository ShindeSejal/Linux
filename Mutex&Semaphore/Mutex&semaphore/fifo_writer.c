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

	for(int i=0; i<2; i++){
		printf("Enter value in arrays:");
		scanf("%d",&arr[i]);
	}


	int fd = open("sum", O_WRONLY);
	if(fd == -1){
		return -1;
	}

	for(int i=0; i<2; i++){
		if(write(fd,&arr,sizeof(arr)) == -1){
			return -1;
		}
	

	printf("The num send at position %d is: %d\n",i+1,arr[i]);

	}	

	close(fd);
}
	return 0;
}


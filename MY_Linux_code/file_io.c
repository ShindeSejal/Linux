/* Normal file I/O Operation*/

#include <stdio.h>

int main(void)
{
	FILE *fptr;
	char buff[20]= "";
	fptr = fopen("Test.txt","r");

	if(!fptr){
		puts("File opening failed\n");
		return -1;
	}

	size_t ret = fread((void *)buff,1,19,fptr);

	printf("Read %lu bytes, String is : %s\n",ret,buff);
	while(1);
	return 0;

}

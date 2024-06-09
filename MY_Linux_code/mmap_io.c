/*Memory mapping Operation*/

#include <stdio.h>
#include <sys/mman.h>

int main(void)
{
        FILE *fptr;
        char buff[20]= "";
        fptr = fopen("Test.txt","r");

        if(!fptr){
                puts("File opening failed\n");
                return -1;
        }

	int fd = fileno(fptr);
	if(fd == -1)
	{
		puts("Descfiptor transfer failed\n");
		return -1;
	}

	void *ptr = mmap(NULL,20,PROT_READ,MAP_PRIVATE,fd,0);
	if(!ptr)
	{
		puts("mmap failed\n");
		return -1;
	}

	puts("Mapping successfull\n");
	printf(" DATA : %s\n",(char *)ptr);
	while(1);
        return 0;

}


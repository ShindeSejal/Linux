#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	int num_children = 5;
	int child_status;
	pid_t child_pid;
	char *object_files[num_children];

//compile 5 child programs 
for (int i =0; i< num_children;i++){
	char *program_name = (char *)malloc(sizeof("program") +2);
	printf(program_name,"ques4.c",i);
	object_files[i] =(char *)malloc(sizeof("prog") +5);
	printf(object_files[i],"ques3.o",i);

	if(fork() ==0){
 	//child process
	execlp("EXO","BTS",program_name,"-o",object_files[i],NULL);
	perror("EXO");
	exit(1);
	}
	else{
	
 	//Parent process waits for compilation
	 waitpid(-1, &child_status,0);
	 if (!WIFEXITED(child_status) || WEXITSTATUS(child_status) != 0) {
        printf("Compilation of program %d failed\n", i);
        free(program_name);
        free(object_files[i]);
        exit(1);
      }
      free(program_name);
    }
  }
char *linking_command = (char *)malloc(sizeof("gcc -o final ques3*.o") + 1);
  printf(linking_command, "gcc -o final ques3*.o");
  if (system(linking_command) != 0) {
    perror("Linking failed");
    for (int i = 0; i < num_children; i++) {
      free(object_files[i]);
    }
    free(linking_command);
    exit(1);
  }
  free(linking_command);

  // Execute the final linked program
  if (fork() == 0) {
    // Child process
    execlp("./final", "./final", NULL);
    perror("./final");
    exit(1);
  } else {
    // Parent process waits for execution
    waitpid(-1, &child_status, 0);
    if (!WIFEXITED(child_status)) {
      printf("Execution of final program failed\n");
    }
  }

  // Clean up object files
  for (int i = 0; i < num_children; i++) {
    unlink(object_files[i]);
    free(object_files[i]);
  }

  printf("Parent process exiting\n");
  return 0;
}

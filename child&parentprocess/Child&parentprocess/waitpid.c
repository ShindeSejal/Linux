#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	int num_children = 5;
	int child_status;
	pid_t child_pid;
	
//create 5 children process
 for(int i =0;i< num_children; i++){
	 child_pid = fork();

	 if(child_pid <0){
		 perror ("fork");
		 exit(1);
	 }
	 else if(child_pid ==0){ //child process
		//child process 1 and 3 to loop
       	if(i ==1 || i ==3){
		while(1){
			sleep(1); 
		}
	}
	else{
		exit(i);
	}
	 }
 }

 //parent process continues here
 //wait for all children to finish 
  for(int i = 0; i< num_children;i++){
	  child_pid = waitpid(-1, &child_status,0);

	  if(child_pid ==-1){
		  perror ("waitpid");
		  exit(1);
	  }
	 if (WIFEXITED(child_status)) {
      printf("Child %d exited with code %d\n", child_pid, WEXITSTATUS(child_status));
    } else if (WIFSIGNALED(child_status)) {
      printf("Child %d terminated abnormally (signal %d)\n", child_pid, WTERMSIG(child_status));
    } else {
      printf("Child %d exited with unknown status\n", child_pid);
    }
  }

  printf("Parent process exiting\n");
  return 0;
}

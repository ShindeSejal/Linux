#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int num_children = 5;
	int child_status;
	pid_t child_pid;
	const char* applications[] ={"Sehun","Suho","Bekhyaun","Chenyeol","kai","D.O"};
	//create 5 children processes
	
	for(int i =0; i < num_children; i++){
		child_pid = fork();

		if(child_pid <0){
			perror("fork");
			exit(1);
		}
		else if (child_pid ==0){ //child process
			execlp(applications[i],applications[i],NULL);
			perror("execlp"); //only if execlp fails
			exit(1);
		}
	}

//parent process continues here

for(int i =0; i< num_children; i++){
	child_pid = waitpid(-1,&child_status, 0);
	if(child_pid ==-1){
		perror("waitpid");
		exit(1);
	}

// check child exit status
  if (WIFEXITED(child_status)) {
      printf("Child %d (application: %s) exited with code %d\n", child_pid, applications[i], WEXITSTATUS(child_status));
    } else if (WIFSIGNALED(child_status)) {
      printf("Child %d (application: %s) terminated abnormally (signal %d)\n", child_pid, applications[i], WTERMSIG(child_status));
    } else {
      printf("Child %d (application: %s) exited with unknown status\n", child_pid, applications[i]);
    }
  }

  printf("Parent process exiting\n");
  return 0;
}

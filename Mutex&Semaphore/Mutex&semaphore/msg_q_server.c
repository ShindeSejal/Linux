#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

#define KEY 1552

struct message{
	long int mtype;
	char mtext[100];
};

int main(){
	int msg_q_id,ret;
	struct message msg;
	char buff[20];



	//Create or get the message queue
	msg_q_id = msgget(KEY, 0666 | IPC_CREAT);
	if(msg_q_id < -1){
		perror("msgget");
		exit(1);
	}
	
	while(1){
		//Prepare msg to send
		printf("Enter data to print\n");
		fgets(buff,20,stdin);
		msg.mtype = 1;
		//strncpy(msg.mtext, "Hello, message queue!");
		strcpy(msg.mtext,buff);

		//send the message
		ret = msgsnd(msg_q_id,&msg,sizeof(struct message), 0);
		if(ret < -1){
			perror("msgsnd");
			exit(1);
		}

		printf("Message sent successfully.\n");
	}		

	return 0;
}



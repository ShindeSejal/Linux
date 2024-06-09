#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define KEY 1552

struct message{
	long int mtype;
	char mtext[100];
};

int main(){
	int msg_q_id,ret;
	struct message msg;

	//Get the message queue
	msg_q_id = msgget(KEY, 0666 | IPC_CREAT);
	if (msg_q_id < 0){
		perror("msgget");
		exit(1);
	}


	while(1){
		//Receive the message
		ret = msgrcv(msg_q_id, &msg, sizeof(struct message), 1, 0);
		if (ret < 0){
			perror("msgrcv");
			exit(1);
		}	

		printf("Received message: %s\n", msg.mtext);
	}
	return 0;
}


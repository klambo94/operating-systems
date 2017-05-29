#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	pid_t processId = fork();

	if(processId < 0) {
		perror("fork() error");
		exit(-1);
	}

	if(processId != 0) {
		printf("Parent PID: %d\n", getpid());
		wait(NULL);
	} else {
		printf("Child PID: %d\n", getpid());
		int returnValue = execl("/home/default/Documents/Programs/processLoop", "processLoop", "5", NULL); //TODO: Question: For the file path of excel how should that be formatted since pathing on my computer will be different than yours. Also mine just doesn't work. 
		if(returnValue == -1) {
			perror("Excel returned an error");
			exit(-1);
		}
		
	}
	return 0;
}
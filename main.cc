#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	int status;
	int statusToPassToCounter = 10;
	pid_t processId = fork();

	if(processId < 0) {
		perror("fork error");
		exit(EXIT_FAILURE);
	}

	if(processId != 0) {
		printf("Parent PID: %d\n", getpid());
		int waitReturn = waitpid(processId, &status, WCONTINUED);
		if(waitReturn < 0) {
			int waitError = errno;
			perror("Error occured during waitpiod\n");
			exit(waitError);
		}

		/*taken from the man pages for wait*/
		if(WIFEXITED(status)) {
			if(WEXITSTATUS(status) != statusToPassToCounter){
				printf("The status returned does not match status passed in.\n");
				printf("Status Passed in: %d Status returned: %d\n", statusToPassToCounter, WEXITSTATUS(status));
				exit(EXIT_FAILURE);
			}
			printf("exited with status=%d\n", WEXITSTATUS(status));
		} else if(WIFSIGNALED(status)) {
			printf("Killed by signal %d\n", WTERMSIG(status));
		} else if(WIFSTOPPED(status)) {
			printf("stopped by signal %d\n", WSTOPSIG(status));
		} else if(WIFCONTINUED(status)) {
			printf("continued\n");
		}
	} else {
		printf("Child PID: %d\n", getpid());
		int excelError = execl("/home/default/Documents/Programs/counter", "counter", 
								"10", NULL);
		if(excelError < 0) {
			int error = errno;
			perror("Error occured during excel");
			exit(error);
		}
	}
	exit(EXIT_SUCCESS);
}
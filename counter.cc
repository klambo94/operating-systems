#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/*
 *Used reference from cpluscplus for atoi.
 *http://www.cplusplus.com/reference/cstdlib/atoi/
 */
int main(int argc, char *argv[]) {
	int n;
	if(argc == 2) {
		n = atoi(argv[1]);
		for(int i = 1; i <= n; i++) {
			printf("Process: %d %d\n", getpid(), i);
		}
	} else {
		printf("Expected argments supplied does not match. Needed 2, entered: %d.\n", argc);
		exit(-1);
	}
	return n;
}

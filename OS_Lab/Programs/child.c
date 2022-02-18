#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
int is_odd (int n) {
	return n % 2 == 1;
}

int main(int argc, char *argv[]) {
	int n = atoi(argv[1]);
	pid_t ret;
	if ((ret = fork()) == -1) {
		perror("Fork");
	} else if (ret == 0) {
		printf(is_odd(n) ? "Odd\n" : "Even\n");
	} else {
		wait(NULL);
	}
	return 0;
}

#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
	int i;
	if (argc < 2) {
		printf("Need at least 1 argument");
		return 1;
	}

	for(i=1;i<argc;i++) {
		int status = unlink(argv[i]);
		if (status == -1) {
			printf("Cannot remove %s\n", argv[i]);
			perror("Unlink Error");
			printf("\n");
		}
	}
	return 0;
}

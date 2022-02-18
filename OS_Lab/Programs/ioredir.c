#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>

// Program 2: Demonstrate use of exec, fork, wait
// This program writes the output of any program to file specified by user
// Using the same strategy used by I/O redirection in unix shells

// The principle is, file descripters survive through
// invocations of execve syscalls

// This program prints PID of parent and child from both processes
// using getpid and getppid calls

int main(int argc, char *argv[]) {
	int fd, forkret;
	if(argc < 3) {
		fprintf(stderr, "Need at least 2 arguments\n");
		return 1;
	}

	fd = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd < 0) {
		perror("Failed to open file");
		return 1;
	}

	// File descriptors survive across execve() calls
	// Using dup2 to clone fd to stdout
	
	dup2(fd, 1); // 1 is stdout

	forkret = fork();
	if (forkret < 0) {
		perror("Fork failed");
		return 1;
	} else if (forkret == 0) {
		fprintf(stderr,
			"Running in child process: pid = %d, parent = %d\n\n",
			(int)getpid(),
			(int)getppid()
		);
		// child process, execute the command
		execvp(argv[2], &argv[2]);
		perror("Exec failed");
	} else {
		fprintf(stderr,
			"Running in parent process: pid = %d, child pid = %d\n\n",
			getpid(),
			forkret
		);
		wait(NULL);
	}
	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

char *append_path(const char *a, const char *b) {
	ssize_t len_a = strlen(a), len_b = strlen(b);
	ssize_t sz = (a[len_a-1] == '/') ? len_a+len_b+1 : len_a+len_b+2;
	char *target = malloc(sz*sizeof(char));
	memcpy(target, a, len_a);

	if (a[len_a-1] != '/') {
		target[len_a] = '/';
		len_a++;
	}
	
	memcpy(target+len_a, b, len_b + 1);
	return target;
}

// name of file given by complete path
const char *file_name(const char *path) {
	char *s;
	if ((s = strrchr(path, '/'))) {
		return s+1;
	}
	return path;
}


void copyfile(char *dest, char *src) {
	struct stat s;
	int statret = stat(dest, &s);
	if (statret != -1 && S_ISDIR(s.st_mode)) {
		dest = append_path(dest, file_name(src));
	}
	// open dest and src
	int dest_fd, r;
	char buf[256];
	int src_fd = open(src, O_RDONLY);
	if (src_fd < 0) {
		perror("Cannot open source file");
		exit(EXIT_FAILURE);
	}

	dest_fd = open(dest, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR); 
	if (dest_fd < 0) {
		perror("Cannot open destination file");
		exit(EXIT_FAILURE);
	}

	while((r=read(src_fd,buf,256)) > 0) {
		write(dest_fd, buf, r);
	}

	if (r != 0) {
		perror("Read failed");
	}
	if (S_ISDIR(s.st_mode)) free(dest);
	return;
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage: %s <src> <dest>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	copyfile(argv[2], argv[1]);
	return 0;
}

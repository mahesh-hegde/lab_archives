#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<unistd.h>

void lsl(const char *path) {
	if (chdir(path) != 0) {
		perror("Cannot change dir");
		return;
	}
	DIR *dir = opendir(".");
	struct dirent *entry = NULL;
	char time[50], p[10] = {'r','w','x','r','w','x','r','w','x','\0'};
	int i, j;

	while((entry = readdir(dir)) != NULL) {
		const char *name = entry->d_name;
		if(name[0] == '.') {
			continue;
			// don't display hidden files
			// including "." and ".."
		}

		struct stat s;
		stat(entry->d_name, &s);
		printf(S_ISDIR(s.st_mode)? "d"
			: S_ISREG(s.st_mode)? "-"
			: S_ISCHR(s.st_mode)? "c"
			: S_ISBLK(s.st_mode)? "b"
			: S_ISLNK(s.st_mode)? "l"
			: S_ISFIFO(s.st_mode)? "f"
			: S_ISSOCK(s.st_mode)? "s"
			: "?"
		);
		for(i = 0, j = (1<<8); i < 9; i++, j>>=1) {
			printf("%c", (s.st_mode & j) ? p[i] : '-');
		}

		printf("%6ld ", (long)s.st_nlink); // number of hard links
		printf("%6s ", getpwuid(s.st_uid)->pw_name); // username
		printf("%6s ", getgrgid(s.st_gid)->gr_name); // groupname
		printf("%6ld ", (long)s.st_size); // size
		strftime(time, sizeof(time), "%c", localtime(&s.st_mtime));
		printf("%s  ", time);
		printf("%s\n", entry->d_name);
	}
}

int main(int argc, char **argv) {
	switch(argc) {
	case 1: lsl(".");
		break;
	case 2: lsl(argv[1]);
		break;
	default: printf("Too many arguments\n");
		return 1;
	}
}

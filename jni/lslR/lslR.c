#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>

void lslR(const char * dirname) {
	DIR * dir = opendir(dirname);
	int is_root = strcmp(dirname, "/") == 0;
	if(!dir) {
		fprintf(stderr, "Cannot open directory %s: %s\n", dirname, strerror(errno));
		exit(EXIT_FAILURE);
	}
	while(1) {
		struct dirent * dentry = readdir(dir);
		if(!dentry) break;
		if(strcmp(dentry->d_name, ".") == 0) continue;
		if(strcmp(dentry->d_name, "..") == 0) continue;
		printf( "%s/%s\n", is_root?"":dirname, dentry->d_name); 
		if(dentry->d_type & DT_DIR) {
			char subdir[PATH_MAX];
			if(strlen(dirname) + strlen(dentry->d_name) + 1 > PATH_MAX) {
				fprintf(stderr, "PATH_MAX exceeded for directory %s/%s\n", is_root?"":dirname, dentry->d_name);
			} else {
				snprintf(subdir, PATH_MAX, "%s/%s", is_root?"":dirname, dentry->d_name);
				lslR(subdir);
			}
		}
	}
	if(closedir(dir)) {
		fprintf(stderr, "Cannot close directory %s: %s\n", dirname, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

int main() {
	lslR("/");
	return 0;
}

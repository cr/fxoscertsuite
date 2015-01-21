#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>

void justprint(const char * name) {
	printf( "%s\n", name); 
}

void recurse_dir(const char * dirname, void (* cb)(const char *)) {
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
		if(strlen(dirname) + strlen(dentry->d_name) + 2 >= PATH_MAX) {
			fprintf(stderr, "PATH_MAX exceeded for directory %s/%s\n", is_root?"":dirname, dentry->d_name);
			continue;
		}
		char fullname[PATH_MAX];
		snprintf(fullname, PATH_MAX, "%s/%s", is_root?"":dirname, dentry->d_name);
		cb(fullname);
		if(dentry->d_type & DT_DIR) recurse_dir(fullname, cb);
	}
	if(closedir(dir)) {
		fprintf(stderr, "Cannot close directory %s: %s\n", dirname, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

int main() {
	recurse_dir("/", justprint);
	return 0;
}

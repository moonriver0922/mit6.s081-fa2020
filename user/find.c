/*************************************************************************
    > File Name: find.c
    > Author: Guosheng_W
    > Mail: 3190102029@zju.edu.cn
    > Created Time: 2022年11月11日 星期五 14时10分45秒
 ************************************************************************/
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char* fmtname(char *path) {

  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), '\0', DIRSIZ-strlen(p));
  return buf;

}


void find(char *path, char *file) {

	int fd;
	struct dirent de;
	struct stat st;
	char buf[512], *p;
	
	if ((fd = open(path, 0)) < 0) {
		fprintf(2, "cannot open %s\n", path);
		return;
	}

	if (fstat(fd, &st) < 0) {
		fprintf(2, "cannot sata %s\n", path);
		return;
	}
	switch (st.type) {
		case T_FILE:
			if (!strcmp(fmtname(path), file)) 
				printf("%s\n", path);
			break;
		case T_DIR:			
			if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
				printf("ls : path  too long\n") ;
				break;
			}
			strcpy(buf, path);
			p = buf + strlen(buf);
			*p++ = '/';
			while (read(fd, &de, sizeof(de)) == sizeof(de)) {
				if (de. inum == 0)
					continue;
				memmove(p, de.name, DIRSIZ);	
				p[DIRSIZ] = 0;
				if (stat(buf, &st) < 0) {
					printf("cannot stat %s\n", buf);
					continue;
				}			
				if (strcmp(fmtname(buf), ".") && strcmp(fmtname(buf), ".."))
					find(buf, file);
			}
			break;
	}
	close(fd);
}

int main(int argc, char *argv[]){


	if (argc < 3) {
		fprintf(2, "input error!\n");
		exit(1);
	}
	
	for (int i = 2; i < argc; i++) {
		find(argv[1], argv[i]);
	}

	exit(0);

}


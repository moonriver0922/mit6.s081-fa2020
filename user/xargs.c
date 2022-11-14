/*************************************************************************
    > File Name: user/xargs.c
    > Author: Guosheng_W
    > Mail: 3190102029@zju.edu.cn
    > Created Time: 2022年11月11日 星期五 20时51分07秒
 ************************************************************************/
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {

	char c[32];
	char *new_argv[MAXARG];
	for(int i = 0; i < argc; i++) {
		new_argv[i] = argv[i];
	}
	while(strlen(gets(c, 256)) != 0) {

		if (c[strlen(c) - 1] == '\n')
			c[strlen(c) - 1] = '\0';
		new_argv[argc] = c;
		/*for (int i = 0; i <= argc; i++) {
			printf("%d %s %d %c\n", &new_argv[i], new_argv[i], &(*new_argv[i]), *new_argv[i]);
		}
		printf("**************\n");
		//argv[argc] = c;
		 for (int i = 0; i <= argc; i++) {
			printf("%d %s %d %c\n", &new_argv[i], new_argv[i], &(*new_argv[i]), *new_argv[i]);
		}
		 printf("*************\n");*/
		new_argv[argc + 1] = 0;
		//argv[argc+1] = 0;
	    /*for (int i = 0; i <= argc + 1; i++) {
			printf("%d %s %d %c\n", &new_argv[i], new_argv[i], &(*new_argv[i]), *new_argv[i]);
		}*/
	
		if(fork() == 0) {	
			//exec(argv[1], argv + 1);
			exec(new_argv[1], new_argv + 1);
			fprintf(2, "exec error!\n");
			exit(1);
		}

		wait(0);
	}

	exit(0);

}

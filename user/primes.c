/*************************************************************************
    > File Name: primes.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2022年11月10日 星期四 16时35分31秒
 ************************************************************************/
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char const *argv[])
{
	int loop = 10;
	int pre = 0;
	int num[1];
	int buf[1];
	int p[2];
	pipe(p);

	for (int i = 2; i <= 35; i++) {
		num[0] = i;
		pre++;
		if (write(p[1], num, 4) != 4) {
			fprintf(2, "write error!\n");
			exit(1);
		}
	}
	while (loop >= 0 && fork() == 0) {
		if (read(p[0], buf, 4) != 4) {
			fprintf(2, "read error!\n");
			exit(1);
		}
		int prime = buf[0];
		printf("prime %d\n", prime);
		int cur = pre;
		for (pre = 0; cur > 1; cur--) {
			if (read(p[0], buf, 4) != 4) {
				fprintf(2, "read error!\n"); 
				exit(1);
			}
			if (buf[0] % prime != 0) {
				pre++;
	 			if (write(p[1], buf, 4) != 4)  {
	 				fprintf(2, "write error!\n ");
					exit(1);
				}
			}
		}
		loop--;
	}

	wait(0);
	exit(0);
}

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int p1[2];
	if(pipe(p1) == -1) return 1;
	int pid = fork();
	if(pid == -1) return 2;
	if(pid == 0){
		//in child process
		int x;
		if(read(p1[0], &x, sizeof(x)) == -1) return 3;
		printf("-> %d\n", x);
		x *= 4;
		if(write(p1[1], &x, sizeof(x)) == -1) return 1;
		printf("Wrote %d\n",x);
	}
	else{
		//parent process
		
	}
	return 0;
}
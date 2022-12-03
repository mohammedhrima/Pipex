#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(void)
{
	int pid = fork();
	if(pid == -1){
		return 1;
	}
	if(pid == 0)
	{
		//child process
		execlp("ping","ping", "-c", "3" ,"google.com", NULL);
	}else{
		//parent process
		wait(NULL);
		printf("Success\n");
		printf("Some new process ");
	}
	return 0;
}
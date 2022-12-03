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
		int err = execlp("ping","ping", "-c", "3" ,"google.con", NULL);
		if(err == -1)
		{
			printf("Could not find program to execute\n");
			return 2;
		}

	}else{
		//parent process
		int wstatus;
		wait(&wstatus);
		if(WIFEXITED(wstatus))
		{
			int statusCode = WEXITSTATUS(wstatus);
			if(statusCode == 0) printf("Success\n");
			else printf("Failure wth status code %d\n",statusCode);
		}
		printf("Some new process ");
	}
	return 0;
}
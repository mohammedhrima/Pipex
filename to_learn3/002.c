#include <stdio.h>
#include <unistd.h>

int main() {
    char* command = "/usr/bin/whereis";
    char* argument_list[] = {"whereis", "ls", NULL,NULL,NULL};

    printf("Before calling execvp()\n");

    printf("Creating another process using fork()...\n");

    if (fork() == 0) {
        // Newly spawned child Process. This will be taken over by "ls -l"
        int status_code = execv(command, argument_list);

        printf("ls -l has taken control of this child process. This won't execute unless it terminates abnormally!\n");

        if (status_code == -1) {
            printf("Terminated Incorrectly\n");
            return 1;
        }
    }
    else {
        // Old Parent process. The C program will come here
        printf("This line will be printed\n");
    }

    return 0;
}

/*
int main(int argc, char **argv)
{
	int fd[2];
	int pid;
	char buf[40];
	fd[0] = open("in", O_CREAT | O_RDWR, 0777);
	fd[1] = open("out", O_CREAT | O_RDWR, 0777);

	if (pipe(fd) < 0)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[0],0);
		write(fd[1], "Hello there", 20);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[1],1);
		read(fd[0], buf, 15);
		close(fd[0]);
		printf("-> %s\n", buf);
	}
	close(fd[0]);
	close(fd[1]);

	return 0;
}
*/
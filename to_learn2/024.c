#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft/libft.h"

// handle all error after
char *ft_getfull_path(char *cmd)
{
	int fd = open("in", O_CREAT | O_TRUNC | O_WRONLY);
	char *path[5] = {"whereis", "ls", NULL, NULL, NULL};
	path[1] = cmd;
	// path[1] = arr[1];
	dup2(fd, STDOUT_FILENO);
	if (execv("/usr/bin/whereis", path) == -1)
		write(1, "Error on executing command\n", 40);
	close(fd);
	
	return NULL;
}

int main(int argc, char **argv)
{
	int status;
	char **arr2;
	char *cmd1, *cmd2;
	int fd[2];
	int pid1, pid2;

	/*arr1 = ft_split(argv[2],' ');
	arr2 = ft_split(argv[2],' ');
	cmd1 = ft_strjoin("/bin/", arr1[0]);
	cmd2 = ft_strjoin("/usr/bin", arr2[0]);
	fd[0] = open(argv[1], O_RDWR | O_CREAT,0777);
	fd[1] = open(argv[4], O_RDWR | O_CREAT, 0777);*/
	//char *arr1[] = {"ls", "-l", NULL, NULL, NULL};
	// ft_getfull_path(arr1);
	/*int fd0 = open("res2", O_CREAT | O_TRUNC | O_WRONLY);
	char *path[5] = {"whereis", "ls", NULL, NULL, NULL};
	// path[1] = arr[1];
	dup2(fd0, STDOUT_FILENO);
	close(fd0);
	if (execv("/usr/bin/whereis", path) == -1)
		write(1, "Error on executing command\n", 40);*/
	int pid = fork();
	if(pid == 0)
		ft_getfull_path("ls");
	if (pid > 0)
	{
		wait(NULL);
		int fd = open("in", O_RDONLY);
		char *res = get_next_line(fd);
		//write(1, res, ft_strlen(res));
		printf("-> %s", res);
		close(fd);
	}

	return 0;
}
#include "pipex.h"

char *cmd_path(char *cmd0, char **paths)
{
	printf("line 5 %s\n", cmd0);
	int i;
	char *cmd1;
	char *cmd2;

	i = 0;
	cmd2 = NULL;
	cmd1 = ft_strjoin("/", cmd0);
	if (access(cmd1, F_OK) == 0 && access(cmd1, X_OK) == 0)
	{
		printf("line 13\n");
		return cmd1;
	}
	printf("line 18 %s\n", paths[i]);
	while (paths && cmd0 && paths[i])
	{
		printf("line 20\n");
		cmd2 = ft_strjoin(paths[i], cmd1);
		printf("--> %s\n", cmd2);
		if (access(cmd2, F_OK) == 0 && access(cmd2, X_OK) == 0)
			return cmd2;
		cmd2 = NULL;
		i++;
	}
	printf("line 27\n");
	return (cmd2);
}

char *grep(char *envp[], char *str)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strstr(envp[i], str))
			return (envp[i]);
		i++;
	}
	return NULL;
}

int Error(char *SHELL)
{
	perror(SHELL);
	return -1;
}

int main(int argc, char *argv[], char *envp[])
{
	//printf("\n================== MAIN ==================\n");
	char **paths;
	int fd[2];
	char **arr1;
	char **arr2;
	char *cmd1;
	char *cmd2;
	char *SHELL;
	int in;
	int out;
	int status;
	pid_t pid1;
	pid_t pid2;

	/*int i = 0;
	while (envp[i])
		printf("-> %s\n", envp[i++]);

	SHELL = ft_strrchr(grep(envp, "SHELL"),'/') + 1;*/
	arr1 = ft_split2(argv[2], ' ', 3);
	arr2 = ft_split2(argv[3], ' ', 3);
	int i = 0;
	while (arr1[i])
	{
		printf("arr1[%d] = %s\n",i,arr1[i]);
		i++;
	}
	i = 0;
	while (arr1[i])
	{
		printf("arr2[%d] = %s\n",i,arr2[i]);
		i++;
	}

	cmd1 = cmd_path(arr1[0], paths);
	cmd2 = cmd_path(arr2[0], paths);
	printf("cmd1 -> %s\n",cmd1);
	printf("cmd2 -> %s\n\n",cmd2);
	return 0;
	in = open(argv[1], O_RDONLY, 0777);
	out = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);

	if (in < 0)
	{
		ft_putendl_fd(ft_strjoin("0. no such file or directory: ", argv[1]), 2);
		//exit(0);
		//close all opened fd
		//close(in);
	}
	if (out < 0) // add && in >= 0
	{
		out = STDOUT_FILENO;
		//perror("0. Error: ");
		//close all opened fd
		//close(out);
		//out = 1;
		//exit(0);
	}
	if (pipe(fd) < 0)
	{
		perror("1. Error: ");
		exit(-1);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("2. Error: ");
		exit(-1);
	}
	if (pid1 == 0)
	{
		dup2(in, STDIN_FILENO);
		//close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (execve(cmd1, arr1, NULL) < 0)
		{
			//char *err;
			//if()
			//read(fd[0],err,30);
			ft_putendl_fd(ft_strjoin("2. no such file or directory: -> ", cmd1), 2);
			exit(-3);
		}
		close(fd[0]);
		close(fd[1]);
		free(cmd1);
		free(arr1);
	}
	if (pid1 > 0)
	{
		wait(NULL);
		waitpid(pid1, &status, 0);
		close(fd[1]);
		free(cmd1);
		free(arr1);
	}

	pid2 = fork();
	if (pid2 < 0)
	{
		perror("3. Error: ");
		exit(-1);
	}
	if (pid2 == 0)
	{
		dup2(out, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
		if (execve(cmd2, arr2, NULL))
		{
			ft_putendl_fd(ft_strjoin("3. no such file or directory: ", cmd2), 2);
			exit(-3);
		}
		close(fd[0]);
		free(cmd2);
		free(arr2);
	}
	if (pid2 > 0)
	{
		wait(NULL);
		close(fd[0]);
		free(cmd2);
		free(arr2);
	}
	return (0);
}
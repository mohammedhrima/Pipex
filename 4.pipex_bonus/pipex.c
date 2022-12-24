/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 04:46:12 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/23 15:23:18 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// #include "Leak_Hunter/leak_hunter.h"

char *get_path_from_env_path(char *cmd1, char **paths)
{
	char *cmd2;
	int	i;

	i = 0;
	while (paths && cmd1 && paths[i])
	{
		cmd2 = ft_strjoin(paths[i], cmd1);
		if (access(cmd2, F_OK) == 0 && access(cmd2, X_OK) == 0)
		{
			free(cmd1);
			return cmd2;
		}
		free(cmd2);
		cmd2 = NULL;
		i++;
	}
	free(cmd1);
	return (cmd2);
}

char *cmd_path(char *cmd0, char **paths)
{
	int i;
	char *cmd1;
	char *cmd2;

	i = 0;
	cmd2 = NULL;
	if (access(cmd0, F_OK) == 0 && access(cmd0, X_OK) == 0)
		return cmd0;
	if(cmd0 && cmd0[0] != '/')
		cmd1 = ft_strjoin("/", cmd0);
	else
		cmd1 = ft_strdup(cmd0);
	if (access(cmd1, F_OK) == 0 && access(cmd1, X_OK) == 0)
		return cmd1;
	return (get_path_from_env_path(cmd1, paths));
}

void Free(char **arr)
{
	int i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

char *grep(char *arr[], char *str)
{
	int i;

	i = 0;
	while (arr && arr[i])
	{
		if (ft_strstr(arr[i], str))
			return (arr[i] + 5);
		i++;
	}
	return NULL;
}

void *allocate1(int len, size_t size)
{
	void *res;

	res = malloc(len * size);
	if (!res)
		exit(1);
	return res;
}
void **allocate2(int len, size_t size, int sublen, size_t subsize)
{
	void **res;
	int i;

	i = 0;
	res = malloc(len * size);
	if (!res)
		exit(1);
	while (i < len)
	{
		res[i] = malloc(sublen * subsize);
		if (!res[i])
		{
			while (i > 0)
			{
				free(res[i]);
				i--;
			}
			free(res);
			exit(1);
		}
		i++;
	}
	return res;
}

void open_pipes(int **pipes, int *i, int len)
{
	while (*i < len)
	{
		if (pipe(pipes[*i]) == -1)
		{
			while (*i > 0)
			{
				close(pipes[*i][0]);
				close(pipes[*i][1]);
				i--;
			}
			perror("Error: ");
			exit(-1);
		}
		(*i)++;
	}
}

int main(int argc, char **argv, char **envp)
{
	int status;

	if (argc < 5)
		exit(1);
	if (ft_strcmp(argv[1], "here_doc") == 0)
		here_doc(argc, argv, envp, &status);
	else
		multi_Pipes(argc, argv, envp, &status);
	//system("leaks pipex");
	return (WEXITSTATUS(status));
}
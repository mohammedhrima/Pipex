/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 04:46:12 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/23 18:41:06 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// #include "Leak_Hunter/leak_hunter.h"

char *get_path_from_env_path(char *cmd1, char **envp)
{
	char *cmd2;
	char **paths;
	int i;

	paths = ft_split(grep(envp, "PATH"), ':');
	i = 0;
	while (paths && cmd1 && paths[i])
	{
		cmd2 = ft_strjoin(paths[i], cmd1);
		if (access(cmd2, F_OK) == 0 && access(cmd2, X_OK) == 0)
		{
			Free(paths);
			free(cmd1);
			return cmd2;
		}
		free(cmd2);
		cmd2 = NULL;
		i++;
	}
	Free(paths);
	free(cmd1);
	return (cmd2);
}

char *cmd_path(char *cmd0, char **envp)
{
	int i;
	char *cmd1;
	char *cmd2;

	i = 0;
	cmd2 = NULL;
	if (ft_strchr(cmd0, '/'))
	{
		if (access(cmd0, F_OK) == 0 && access(cmd0, X_OK) == 0)
			return cmd0;
		return NULL;
	}
	if (cmd0 && cmd0[0] != '/')
		cmd1 = ft_strjoin("/", cmd0);
	else
		cmd1 = ft_strdup(cmd0);
	if (access(cmd1, F_OK) == 0 && access(cmd1, X_OK) == 0)
		return cmd1;
	return (get_path_from_env_path(cmd1, envp));
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

void open_pipes(t_var _, int i)
{
	while (i < _.num)
	{
		if (pipe(_.pipes[i]) == -1)
		{
			while (i > 0)
			{
				close(_.pipes[i][0]);
				close(_.pipes[i][1]);
				i--;
			}
			perror("Error: ");
			exit(-1);
		}
		(i)++;
	}
}

void get_cmd_path_and_close_pipes(t_var *_, int i, char *argv, char **envp)
{
	_->arr = ft_split2(argv, ' ', 3);
	_->cmd = cmd_path(_->arr[0], envp);
	if (!_->cmd)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(_->arr[0], 2);
	}
	int j = 0;
	while (j < _->num + _->k)
	{
		if (i != j)
			close(_->pipes[j][0]);
		if (i + 1 != j)
			close(_->pipes[j][1]);
		j++;
	}
	dup2(_->pipes[i][0], STDIN_FILENO);
	dup2(_->pipes[i + 1][1], STDOUT_FILENO);
}

void Fork(t_var _, int i, char **envp)
{
	_.pids[i] = fork();
	if (_.pids[i] == -1)
	{
		perror("Error: ");
		exit(-1);
	}
	if (_.pids[i] == 0)
	{
		get_cmd_path_and_close_pipes(&_, i, _.argv[i + 3 - _.k], envp);
		if (execve(_.cmd, _.arr, envp) == -1)
		{
			if (i == 2)
				exit(127);
			else
				exit(0);
		}
	}
	else if (_.pids[i] > 0)
	{
		close(_.pipes[i][0]);
		close(_.pipes[i + 1][1]);
	}
}

int main(int argc, char **argv, char **envp)
{
	int status;

	if (argc < 5)
		exit(1);
	if (ft_strcmp(argv[1], "here_doc") == 0)
		here_doc_func(argc, argv, envp, &status);
	else
		multi_pipes_func(argc, argv, envp, &status);
	// system("leaks pipex");
	return (WEXITSTATUS(status));
}
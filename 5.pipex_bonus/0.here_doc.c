/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.here_doc.__.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 09:57:50 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/23 19:10:36 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void Exec_first_cmd(t_var2 *__, char **argv)
{
	char *str;
	char *tmp;
	char *c;

	__->Exit = argv[2];
	if (pipe(__->pipes2) == -1)
	{
		perror("Error: ");
		exit(-1);
	}
	str = NULL;
	c = ft_calloc(2, 1);
	while (!str || ft_strcmp(str, __->Exit))
	{
		free(str);
		str = ft_calloc(1, 1);
		while (read(STDIN_FILENO, c, 1) >= 0 && *c != '\n')
		{
			tmp = ft_strjoin(str, c);
			free(str);
			str = tmp;
		}
		if (ft_strcmp(str, __->Exit))
		{
			ft_putendl_fd(str, __->pipes2[1]);
		}
	}
	free(str);
}

void here_doc_func(int argc, char **argv, char **envp, int *status)
{
	t_var2 __;
	t_var _;

	Exec_first_cmd(&__, argv);
	close(__.pipes2[1]);
	close(__.pipes2[0]);
	free(__.c);
	_.num = 2;
	_.k = 0;
	_.pids = (int *)allocate1(3, sizeof(int));
	//_.pipes = (int **)malloc(3 * sizeof(int *));
	_.pipes = (int **)allocate2(3, sizeof(int *), 2, sizeof(int));
	_.cmd = NULL;
	_.arr = NULL;
	_.pipes[2][1] = open_file(argv[argc - 1], 'a');
	_.argv = argv;
	open_pipes(_, 0);
	func(&_, status, envp, 3);
}
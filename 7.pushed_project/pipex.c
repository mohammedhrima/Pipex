/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 04:46:12 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/24 08:12:35 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	status;

	if (argc < 5)
		exit(1);
	if (ft_strcmp(argv[1], "here_doc") == 0)
		here_doc(argc, argv, envp, &status);
	else
		multi_pipes(argc, argv, envp, &status);
	return (WEXITSTATUS(status));
}

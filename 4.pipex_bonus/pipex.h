/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 08:09:37 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/23 14:42:36 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft/libft.h"
#include <errno.h>
#include <string.h>

char *get_path_from_env_path(char *cmd1, char **paths);
char *cmd_path(char *cmd0, char **paths);
void Free(char **arr);
char *grep(char *arr[], char *str);
void here_doc(int argc, char **argv, char **envp, int *status);
void multi_Pipes(int argc, char **argv, char **envp, int *status);
void *allocate1(int len, size_t size);
void **allocate2(int len, size_t size, int sublen, size_t subsize);
void open_pipes(int **pipes, int *i, int len);

#endif

/*
protect all mallocs
*/
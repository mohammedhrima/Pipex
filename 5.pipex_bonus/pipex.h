/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 08:09:37 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/24 04:27:55 by mhrima           ###   ########.fr       */
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

typedef struct s_var
{
	int **pipes;
	int num;
	int *pids;
	char *cmd;
	char **arr;
	char **argv;
	int k;
} t_var;

typedef struct s_var2
{
	char *Exit;
	int pipes2[2];
	char *c;
	char *tmp;
} t_var2;

char *get_path_from_env_path(char *cmd1, char **paths);
char *cmd_path(char *cmd0, char **paths);
void Free(char **arr);
char *grep(char *arr[], char *str);
void here_doc_func(int argc, char **argv, char **envp, int *status);
void Exec_first_cmd(t_var2 *__, char **argv);

void multi_pipes_func(int argc, char **argv, char **envp, int *status);
void *allocate1(int len, size_t size);
void **allocate2(int len, size_t size, int sublen, size_t subsize);
void open_pipes(t_var _, int i);
int open_file(char *name, char type);
void Fork(t_var _, int i, char **envp);
void func(t_var *_, int *status, char **envp, int l);


#endif

/*
protect all mallocs
*/
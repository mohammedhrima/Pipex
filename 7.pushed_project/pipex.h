/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 08:09:37 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/24 09:10:26 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct a
{
	char	**argv;
	int		**pipes;
	char	**envp;
	int		*pids;
}			t_a;

typedef struct h_d
{
	int		pipes2[2];
	char	*str1;
	char	*str2;
	char	*tmp;
}			t_b;

char		*path_from_env_path(char *cmd1, char **envp);
char		*cmd_path(char *cmd0, char **envp);
void		*allocate_1d(int len, size_t size);
void		**allocate_2d(int len, size_t size, int sublen, size_t subsize);
void		free_arr(char **arr);
void		check_cmd(char *cmd, char **arr);
void		close_pipes(t_a *var, int len, int current_index);
void		open_pipes(int **pipes, int i, int len);
char		*grep(char *arr[], char *str);
int			open_file(char *name, char type);
void		fork_func_h(t_a var);
void		close_pipes_wait_pids_h(t_a var, int *status);
void		read_form_her_doc(t_b *var, char *Exit);
void		open_here_doc(char *Exit);
void		here_doc(int argc, char **argv, char **envp, int *status);
void		child_process_h(t_a *var, char *argv_i, int pipes_len, int i);
void		fork_func_m(t_a *var, int pipes_len);
void		close_pipes_wait_pids_m(t_a var, int pipes_len, int *status);
void		multi_pipes(int argc, char **argv, char **envp, int *status);
void		child_process_m(t_a *var, char *argv_i, int pipes_len, int i);
char		*grep(char *arr[], char *str);
int			ft_strcmp(const char *s1, const char *s2);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
size_t		ft_strlen(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin2(char *s1, char *s2);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		**ft_split2(char const *s, char c, int len);
char		*ft_strstr(char *from, char *to_find);
char		*ft_strdup(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strchr(const char *s, int c);

#endif

#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"
#include <fcntl.h>

int main(void)
{
	char *Exit = "close";
	int pipes[2];
	if (pipe(pipes) < 0)
		printf("Error openning pipe\n");
	int out = open("out", O_RDWR | O_CREAT, 0777);
	char *str = NULL;
	while (ft_strcmp(str, Exit))
	{
		str = get_next_line(STDIN_FILENO);
		ft_putendl_fd(str, pipes[1]);
	}
	str = NULL;
	str = get_next_line(pipes[0]);
	while (ft_strcmp(str, Exit))
	{
		ft_putendl_fd(str, STDOUT_FILENO);
		str = get_next_line(pipes[0]);
	}
	close(pipes[0]);
	close(pipes[1]);
	exit(0);
}
#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"
#include <fcntl.h>

int main(void)
{
	char *Exit = "close";
	/*char *res = ft_strstr("nvhfbjdfhbdjbclosejbfhbfhfbffj", Exit);
	printf("-> %s\n", res);*/
	int pipes[2];
	if (pipe(pipes) < 0)
		printf("Error openning pipe\n");
	int out = open("out", O_RDWR | O_CREAT, 0777);
	//dup2(pipes[0], STDIN_FILENO);
	//dup2(pipes[1], STDOUT_FILENO);
	dup2(out, STDOUT_FILENO);
	char *str = NULL;
	while (ft_strcmp(str, Exit))
	{
		//str = get_next_line(pipes[0]);
		str = get_next_line(STDIN_FILENO);
		ft_putendl_fd(str, 1);
		//printf("->%s\n", str);
	}
	close(pipes[0]);
	close(pipes[1]);
	printf("Exit process\nstr = %s\n",str);
	exit(0);
}
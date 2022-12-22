#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"

int main(void)
{
	int pipes[2];
	if(pipe(pipes) < 0)
		printf("Error openning pipe\n");
	//dup2(pipes[0], STDIN_FILENO);
//	dup2(pipes[1], STDOUT_FILENO);
	char *str = NULL;
	while (!ft_strchr(str, 'a'))
	{
		str = get_next_line(STDIN_FILENO);
		//printf("->%s\n", str);
	}
	printf("Exit process\n");
	exit(0);
}
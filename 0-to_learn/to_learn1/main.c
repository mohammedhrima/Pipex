#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("CTRL + C");
		exit(EXIT_SUCCESS);
	}
}

int	main(void)
{
	while (1)
	{
		signal(SIGINT, signal_handler);
	}
	return (0x0);
}
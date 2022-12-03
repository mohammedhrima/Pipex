#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int main(char *infile, char *cmd1, char *cmd2,  char *outfile )
{
//	int id = fork();
//	printf("this is process %d - %d\n", id, getpid());
	int infd =  open(infile, O_RDWR);
	dup2(infd, 0);
	
}
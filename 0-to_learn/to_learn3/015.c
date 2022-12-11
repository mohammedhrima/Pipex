#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd = open("in2", O_RDWR);
	if(fd < 0)
		printf("error");
	return 0;
}
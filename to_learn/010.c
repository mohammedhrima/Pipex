#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd1 = open("file.txt", O_WRONLY);
	if(fd1 < 0)	printf("Error openning file\n");
	dup2(fd1,2);//copy fd1 to file descriptor 2
	write(fd1, "text number 1", 13);
	write(2, "text number 2", 13);
	printf("fd1 -> %d\n", fd1);
//	printf("fd2 -> %d\n", fd2);
}
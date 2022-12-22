#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int fd = open("file.txt", O_CREAT | O_RDWR, 0777);
	write(fd, "hey\n", 5);
	write(fd, "hey2\n", 5);
	write(fd, "hey3\n", 5);

	close(fd);
}
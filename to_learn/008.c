#include <unistd.h>

int main(void)
{
	int id;
	id = fork();
	if(id != 0)
	{
		fork();
	}
	
	printf("hey\n");
	return (0);
}
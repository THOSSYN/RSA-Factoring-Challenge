#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/**
 *GetFactors - factorizes a number
 *@n: is the number
 *Return: Nothing
 */

void GetFactors(int n)
{
	int i;

	while (n > 1)
	{
		for (i = 2; i <= n; i++)
		{
			if (n % i == 0)
			{
				printf("%d =%d*%d\n", n, n / i, i);
				/*n /= i;*/
				return;
			}
		}
	}
}
/**
 *main - Reads content of a file
 *@ac: is the number of argument on the command line
 *@av: is the second argument of the commandline
 *Return: 0
 */

int main(int ac, char **av)
{
	char *lineptr = NULL;
	size_t nread = 0;
	int fd = STDIN_FILENO, number;
	FILE *fptr;

	if (ac != 2)
	{
		dprintf(2, "Usage: %s <file>\n", av[0]);
		exit(0);
	}
	if (ac > 1)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			dprintf(2, "Usage: %s <file>\n", av[1]);
			exit(EXIT_FAILURE);
		}
	}
	if (fd != STDIN_FILENO)
	{
		fptr = fdopen(fd, "r");
	}
	else
	{
		fptr = stdin;
	}
	while ((nread = getline(&lineptr, &nread, fptr)) != -1)
	{
		number = atoi(lineptr);
		GetFactors(number);
	}
	close(fd);
	return (0);
}

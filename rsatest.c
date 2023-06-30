#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * IsprimeFact - Checks a divisor primality
 * @num: is the number to be checked
 * Return: True or False
 */
bool IsprimeFact(long int num)
{
	long int i;

	/*Iterate from 2 till number less than one*/
	for (i = 2; i < num; i++)
	{
		if (num % i == 0)
			return (false);
	}
	return (true);
}

/**
 * GetFactors - Factorizes a prime number
 * @num: is the prime number
 * Return: nothing
 */

void GetFactors(long int num)
{
	long int divv;

	/*we start using 2 through num = square of divv*/
	for (divv = 2; divv * divv <= num; divv++)
	{
		if (num % divv == 0 && IsprimeFact(divv))
		{
			printf("%ld =%ld*%ld\n", num, num / divv, divv);
		}
	}
}

/**
 *main - get the number per line from the file
 *@argc: is the number of argument
 *@argv: is the array of string passed to the program
 *Return: 0 on success
 */

int main(int argc, char **argv)
{
	char *lineptr = NULL;
	size_t nread = 0;
	int fd = STDIN_FILENO;
	FILE *fptr;

	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			fprintf(stderr, "Usage: %s <file>\n", argv[1]);
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

	long int number;

	while ((nread = getline(&lineptr, &nread, fptr)) != -1)
	{
		number = strtol(lineptr, NULL, 10);
		GetFactors(number);
	}

	free(lineptr);
	fclose(fptr);
	close(fd);

	return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <gmp.h>

void getFactors(mpz_t number) {
    mpz_t factor, quotient;
    mpz_inits(factor, quotient, NULL);

    mpz_set(quotient, number);

    mpz_nextprime(factor, factor);
    while (mpz_cmp(factor, quotient) <= 0) {
        if (mpz_divisible_p(quotient, factor)) {
            mpz_divexact(quotient, quotient, factor);
            gmp_printf("%Zd=%Zd*%Zd\n", number, quotient, factor);
            break;
        }
        mpz_nextprime(factor, factor);
    }

    mpz_clears(factor, quotient, NULL);
}

int main(int ac, char **av) {
    if (ac != 2) {
        dprintf(2, "Usage: factors <file>\n");
        exit(EXIT_FAILURE);
    }

    int fd = open(av[1], O_RDONLY);
    if (fd == -1) {
        dprintf(2, "Error opening the file: %s\n", av[1]);
        exit(EXIT_FAILURE);
    }

    FILE *fptr = fdopen(fd, "r");
    if (fptr == NULL) {
        dprintf(2, "Error opening the file: %s\n", av[1]);
        close(fd);
        exit(EXIT_FAILURE);
    }

    char *lineptr = NULL;
    size_t nread = 0;
    ssize_t read;
    
    mpz_t number;
    mpz_init(number);

    while ((read = getline(&lineptr, &nread, fptr)) != -1) {
        if (lineptr[read - 1] == '\n') {
            lineptr[read - 1] = '\0';  // Remove the trailing newline character
        }

        if (mpz_set_str(number, lineptr, 10) != 0) {
            dprintf(2, "Invalid number format: %s\n", lineptr);
            continue;
        }

        if (mpz_cmp_ui(number, 1) <= 0) {
            dprintf(2, "Number must be greater than 1: %s\n", lineptr);
            continue;
        }

        getFactors(number);
    }

    free(lineptr);
    fclose(fptr);
    close(fd);
    mpz_clear(number);
    return 0;
}


/*#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
*/
/**
 *GetFactors - factorizes a number
 *@n: is the number
 *Return: Nothing
 */

/*void GetFactors(int n)
{
	int i;

	while (n > 1)
	{
		for (i = 2; i <= n; i++)
		{
			if (n % i == 0)
			{
				printf("%d =%d*%d\n", n, n / i, i);
				n /= i;
				return;
			}
		}
	}
}*/
/**
 *main - Reads content of a file
 *@ac: is the number of argument on the command line
 *@av: is the second argument of the commandline
 *Return: 0
 */

/*int main(int ac, char **av)
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
}*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

bool IsprimeFact(long int num) {
    long int i;

    for (i = 2; i < num; i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}

long int PollardRho(long int num) {
    long int x = 2, y = 2, d = 1;
    long int c;

    srand(1);
    c = rand() % (num - 1) + 1;

    while (d == 1) {
        x = (x * x + c) % num;
        y = (y * y + c) % num;
        y = (y * y + c) % num;
        d = abs(x - y) % num;
    }

    return d;
}

long int ModularExponentiation(long int base, long int exponent, long int modulus) {
    long int result = 1;
    base = base % modulus;

    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;

        base = (base * base) % modulus;
        exponent /= 2;
    }

    return result;
}
void GetFactors(long int num)
{
    long int divv;

    while (num % 2 == 0) {
        printf("%ld=%ld*2\n", num, num / 2);
        num = num / 2;
    }

    for (divv = 3; divv * divv <= num; divv += 2) {
        while (num % divv == 0) {
            printf("%ld=%ld*%ld\n", num, num / divv, divv);
            num = num / divv;
        }
    }

    if (num > 2) {
        printf("%ld=%ld*%ld\n", num, num, 1L);
    }
}
/*long int ModularExponentiation(long int base, long int exponent, long int modulus) {
    long int result = 1;
    base = base % modulus;

    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;

        base = (base * base) % modulus;
        exponent /= 2;
    }

    return result;
}

void GetFactors(long int num) {
    printf("%ld =", num);

    while (num % 2 == 0) {
        printf(" 2");
        num = num / 2;
    }

    for (long int divv = 3; divv * divv <= num; divv += 2) {
        while (num % divv == 0) {
            printf(" %ld", divv);
            num = num / divv;
        }
    }

    if (num > 2) {
        printf(" %ld", num);
    }

    printf("\n");
}*/

int main(int argc, char **argv)
{
    char *lineptr = NULL;
    size_t bufsize = 0;
    ssize_t nread;
    int fd = STDIN_FILENO;
    FILE *fptr;

    if (argc > 1) {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
            fprintf(stderr, "Usage: %s <file>\n", argv[1]);
            exit(EXIT_FAILURE);
        }
    }

    if (fd != STDIN_FILENO) {
        fptr = fdopen(fd, "r");
    } else {
        fptr = stdin;
    }

    long int number;

    while ((nread = getline(&lineptr, &bufsize, fptr)) != -1) {
        number = strtol(lineptr, NULL, 10);
        GetFactors(number);
    }

    free(lineptr);
    fclose(fptr);
    close(fd);

    return 0;
}

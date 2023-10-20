#include "shell.h"

int my_erratoi(char *siz)
{
	int a = 0;
	unsigned long int check = 0;

	if (*siz == '+')
		siz++;

	a = 0;
	while (siz[a] != '\0')
	{
		switch (siz[a])
		{
			case '0' ... '9':
				check *= 10;
				check += (siz[a] - '0');
				if (check > INT_MAX)
					return (-1);
				break;
			default:
				return (-1);
		}
		a++;
	}

	return ((int)check);
}

void print_error(info_t *inf, char *chestr)
{
	my_eputs(inf->my_f_name);
	my_eputs(": ");
	my_printd(inf->my_linecount, STDERR_FILENO);
	my_eputs(": ");
	my_eputs(inf->my_argv[0]);
	my_eputs(": ");
	my_eputs(chestr);
}

int my_printd(int put, int fid)
{
	int (*my__putchar)(char) = (fid == STDERR_FILENO) ? my_eputchar : my_putchar;
	int counter = 0;
	unsigned int rebase = (put < 0) ? -put : put;

	switch (put < 0)
	{
		case 1:
			my__putchar('-');
			counter++;
			break;
		default:
			break;
	}

	while (rebase > 0)
	{
		int mydigit = rebase % 10;

		my__putchar('0' + mydigit);
		rebase /= 10;
		counter++;
	}

	return (counter);
}

char *my_convertnumber(long int number, int bases, int flgs)
{
	static char *myarray;
	static char mybuffer[50];
	char mysign = 0;
	char *pointer;
	unsigned long nums = number;

	if (!(flgs & MY_CONVERTUNSIGNED) && number < 0)
	{
		nums = -number;
		mysign = '-';
	}

	myarray = flgs & MY_CONVERTLOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &mybuffer[49];
	*pointer = '\0';

	for (; nums != 0; nums /= bases)
	{
		*--pointer = myarray[nums % bases];
	}

	if (mysign)
		*--pointer = mysign;
	return (pointer);
}

void my_removecomments(char *buffer)
{
	int a = 0;

	while (buffer[a] != '\0')
	{
		if (buffer[a] == '#' && (!a || buffer[a - 1] == ' '))
		{
			buffer[a] = '\0';
			break;
		}
		a++;
	}
}
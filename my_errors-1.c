#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in the string, converted number otherwise
 *         -1 on error
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	i = 0;
	while (s[i] != '\0')
	{
		switch (s[i])
		{
			case '0' ... '9':
				result *= 10;
				result += (s[i] - '0');
				if (result > INT_MAX)
					return (-1);
				break;
			default:
				return (-1);
		}
		i++;
	}

	return ((int)result);
}
/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}
/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = (fd == STDERR_FILENO) ? _eputchar : _putchar;
	int count = 0;
	unsigned int _abs_ = (input < 0) ? -input : input;

	switch (input < 0)
	{
		case 1:
			__putchar('-');
			count++;
			break;
		default:
			break;
	}

	while (_abs_ > 0)
	{
		int digit = _abs_ % 10;

		__putchar('0' + digit);
		_abs_ /= 10;
		count++;
	}

	return (count);
}
/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	for (; n != 0; n /= base)
	{
		*--ptr = array[n % base];
	}

	if (sign)
		*--ptr = sign;
	return (ptr);
}
/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int i = 0;

	while (buf[i] != '\0')
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
		i++;
	}
}


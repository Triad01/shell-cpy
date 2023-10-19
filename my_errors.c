#include "shell.h"
/**
 * _eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		switch (str[i])
		{
			case '\0':
				return;
			default:
				_eputchar(str[i]);
		}
		i++;
	}
}
/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	switch (c)
	{
		case BUF_FLUSH:
			write(2, buf, i);
			i = 0;
			break;
		default:
			if (i >= WRITE_BUF_SIZE)
			{
				write(2, buf, i);
				i = 0;
			}
			buf[i++] = c;
	}
	return 1;
}
/**
 * _putfd - writes the character c to the given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	switch (c)
	{
		case BUF_FLUSH:
			write(fd, buf, i);
			i = 0;
			break;
		default:
			if (i >= WRITE_BUF_SIZE)
			{
				write(fd, buf, i);
				i = 0;
			}
			buf[i++] = c;
	}
	return 1;
}
/**
 * _putsfd - prints an input string to the given file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		_putfd(str[i], fd);
	}

	return i;
}


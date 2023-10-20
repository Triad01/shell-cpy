#include "shell.h"
/**
 * my_inputbuffers - buffers the chained commands
 * @inf: first parameter
 * @buffer: contains address of the buffer
 * @length: cotains address of length variable
 * Return: bytes read
 */

ssize_t my_inputbuffers(info_t *inf, char **buffer, size_t *length);
ssize_t my_inputbuffers(info_t *inf, char **buffer, size_t *length)
{
	ssize_t real = 0;
	size_t len_pointer = 0;

	switch (*length)
	{
	case 0:
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, my_sigintHandler);

#if MYUSE_GETLINER
		real = getline(buffer, &len_pointer, stdin);
#else
		real = my_getline(inf, buffer, &len_pointer);
#endif

		if (real > 0)
		{
			if ((*buffer)[real - 1] == '\n')
			{
				(*buffer)[real - 1] = '\0';
				real--;
			}
			inf->mylineflag = 1;
			my_removecomments(*buffer);
			my_buildhistorylist(inf, *buffer, inf->hcount++);

			if (my_strchr(*buffer, ';'))
			{
				*length = real;
				inf->mycmduf = buffer;
			}
		}
		break;

	default:
		break;
	}

	return (real);
}
/**
 * my_getinput - gets input from stream
 * @inf: parameter struct
 * Return: always an unsigned int
 */
ssize_t my_getinput(info_t *inf)
{
	static char *buffer;
	static size_t a, b, length;
	ssize_t real = 0;
	char **buf = &(inf->argsm), *point;

	switch (real = my_inputbuffers(inf, &buffer, &length))
	{
	case -1:
		return (-1);
	default:
		break;
	}

	if (length)
	{
		b = a;
		point = buffer + a;

		my_checkchain(inf, buffer, &b, a, length);

		for (; b < length; b++)
		{
			if (my_ischain(inf, buffer, &b))
			{
				break;
			}
		}

		a = b + 1;
		if (a >= length)
		{
			a = length = 0;
			inf->cmdtype = MYCMDSNORMER;
		}

		*buf = point;
		return (my_strlen(point));
	}

	*buf = buffer;
	return (real);
}
/**
 * my_readbuf - reads a items of a buffer
 * @inf: parameter struct
 * @buffer: buffer
 * @in: size
 * Return: always an unsigned int
 */
ssize_t my_readbuf(info_t *inf, char *buffer, size_t *in)
{
	ssize_t real = 0;

	switch (*in)
	{
	case 0:
		real = read(inf->reader, buffer, MYREADSIZE);
		if (real >= 0)
		{
			*in = real;
		}
		return (real);
	default:
		return (0);
	}
}
/**
 * my_getline - gets the next line of input from an input stream
 * @inf: parameter struct
 * @pointer: address of pointer to buffer
 * @len: size of allocated pointer buffer
 * Return: always an integer
 */
int my_getline(info_t *inf, char **pointer, size_t *len)
{
	static char buffer[MYREADSIZE];
	static size_t a, length;
	size_t b;
	ssize_t real = 0, c = 0;
	char *point = NULL, *mynew_point = NULL, *d;

	switch (point = *pointer, a == length)
	{
	case 1:
		a = length = 0;
	default:
		break;
	}

	real = my_readbuf(inf, buffer, &length);
	if (real == -1 || (real == 0 && length == 0))
	{
		return (-1);
	}

	d = my_strchr(buffer + a, '\n');
	b = d ? 1 + (unsigned int)(d - buffer) : length;
	mynew_point = my_realloc(point, c, c ? c + b : b + 1);

	switch (!mynew_point)
	{
	case 1:
		if (point)
		{
			free(point);
		}
		return (-1);
	default:
		break;
	}

	if (c)
	{
		my_strncat(mynew_point, buffer + a, b - a);
	}
	else
	{
		my_strncpy(mynew_point, buffer + a, b - a + 1);
	}

	c += b - a;
	a = b;
	point = mynew_point;

	if (len)
	{
		*len = c;
	}
	*pointer = point;
	return (c);
}
/**
 * my_sigintHandler - blocks ctrl-C functions
 * @mysigum: the signal number
 */
void my_sigintHandler(__attribute__((unused)) int mysigum)
{
	my_puts("\n");
	my_puts("$ ");
	my_putchar(MYBUFLUSH);
}

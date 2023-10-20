#include "shell.h"

void my_eputs(char *strings)
{
	int a = 0;

	if (!strings)
		return;

	while (strings[a] != '\0')
	{
		switch (strings[a])
		{
			case '\0':
				return;
			default:
				my_eputchar(strings[a]);
		}
		a++;
	}
}

int my_eputchar(char cha)
{
	static int a;
	static char buffer[MY_WRITEBUFSIZE];

	switch (cha)
	{
	case MYBUFLUSH:
		write(2, buffer, a);
		a = 0;
		break;
	default:
		if (a >= MY_WRITEBUFSIZE)
		{
			write(2, buffer, a);
			a = 0;
		}
		buffer[a++] = cha;
	}
	return (1);
}

int my_putfd(char cha, int fid)
{
	static int a;
	static char buffer[MY_WRITEBUFSIZE];

	switch (cha)
	{
	case MYBUFLUSH:
		write(fid, buffer, a);
		a = 0;
		break;
	default:
		if (a >= MY_WRITEBUFSIZE)
		{
			write(fid, buffer, a);
			a = 0;
		}
		buffer[a++] = cha;
	}
	return (1);
}

int my_putsfd(char *strings, int fid)
{
	int a = 0;

	if (!strings)
		return 0;

	for (a = 0; strings[a] != '\0'; a++)
	{
		my_putfd(strings[a], fid);
	}

	return (a);
}
#include "shell.h"

char *my_strcpy(char *destin, char *source)
{
	int in;

	if (destin == source || source == 0)
		return (destin);

	for (in = 0; source[in]; in++)
	{
		destin[in] = source[in];
	}

	destin[in] = '\0';

	return (destin);
}

char *my_strdup(const char *string)
{
	int in;

	if (string == NULL)
		return (NULL);

	int len = 0;
	while (string[len])
		len++;

	char *retset = malloc(sizeof(char) * (len + 1));
	if (retset == NULL)
		return (NULL);

	for (in = 0; in <= len; in++)
	{
		retset[in] = string[in];
	}

	return (retset);
}

void my_puts(char *strings)
{
	int i;
	if (!strings)
		return;

	for (i = 0; strings[i] != '\0'; i++)
	{
		my_putchar(strings[i]);
	}
}

int my_putchar(char character)
{
	static int in;
	static char buffs[MY_WRITEBUFSIZE];

	if (character == MYBUFLUSH || in >= MY_WRITEBUFSIZE)
	{
		write(1, buffs, in);
		in = 0;
	}
	if (character != MYBUFLUSH)
		buffs[in++] = character;
	return (1);
}

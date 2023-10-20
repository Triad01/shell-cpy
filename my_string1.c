#include "shell.h"
/**
 * my_strcpy - copies a string into another string
 * @destin: the destination string
 * @source: the source string
 * Return: pointer to destination string
 */
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
/**
 * my_strdup - duplicates a string
 * @string: the string to be duplicated
 * Return: pointer to the duplicated string
 */
char *my_strdup(const char *string)
{
	char *retset;
	int in, len;

	if (string == NULL)
		return (NULL);

	len = 0;

	while (string[len])
		len++;

	retset = malloc(sizeof(char) * (len + 1));

	if (retset == NULL)
		return (NULL);

	for (in = 0; in <= len; in++)
	{
		retset[in] = string[in];
	}

	return (retset);
}
/**
 * my_puts - prints an input string to the stdout
 * @strings: the string to be printed
 */
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
/**
 * my_putchar - writes the character stdout
 * @character: The character to print
 * Return: always an integer
 */
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

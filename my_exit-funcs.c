#include "shell.h"
/**
 **my_strncpy - copies a string
 *@destin: destination string to be copied to
 *@source: the source string
 *@num: the amount of characters to be copied
 *Return: the concatenated string
 */
char *my_strncpy(char *destin, char *source, int num);
char *my_strncpy(char *destin, char *source, int num)
{
	char *sy = destin;
	int a;

	for (a = 0; a < num - 1 && source[a] != '\0'; a++)
	{
		destin[a] = source[a];
	}

	for (; a < num; a++)
	{
		destin[a] = '\0';
	}

	return (sy);
}
/**
 **my_strncat - concatenates two strings
 *@destin: the first string
 *@source: the second string
 *@num: the max bytes to be used
 *Return: the concatenated string
 */
char *my_strncat(char *destin, char *source, int num)
{
	char *sy = destin;
	int a, b;

	for (a = 0; destin[a] != '\0'; a++)
	{
	}

	for (b = 0; source[b] != '\0' && b < num; b++)
	{
		destin[b] = source[b];
		b++;
	}

	if (b < num)
	{
		destin[b] = '\0';
	}

	return (sy);
}
/**
 **my_strchr - locates a character in a string
 *@sy: the string which is passed
 *@cy: the character to search for in string sy
 *Return: a pointer to the memory area of the sting
 */
char *my_strchr(char *sy, char cy)
{
	for (; *sy != '\0'; sy++)
	{
		if (*sy == cy)
		{
			return (sy);
		}
	}

	return (NULL);
}

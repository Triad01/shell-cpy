#include "shell.h"
/**
 * my_strlen - finds the length of a string
 * @sh: the string
 * Return: always an integer (length of string)
 */
int my_strlen(char *sh)
{
	int in = 0;

	if (!sh)
		return (0);

	for (; sh[in] != '\0'; in++)
	{
	}

	return (in);
}
/**
 * my_strcmp - compares two strings
 * @sh1: the first string to be compared
 * @sh2: the second string to be compared
 * Return: always an integer
 */
int my_strcmp(char *sh1, char *sh2)
{
	for (; *sh1 && *sh2; sh1++, sh2++)
	{
		if (*sh1 != *sh2)
			return (*sh1 - *sh2);
	}

	if (*sh1 == *sh2)
		return (0);
	else
		return (*sh1 < *sh2 ? -1 : 1);
}
/**
 * my_startswith - checks if an input string starts with haystack
 * @mypaystack: string to search
 * @myneed: the substring to search for
 * Return: address of next char
 */
char *my_startswith(const char *mypaystack, const char *myneed)
{
	for (; *myneed; myneed++, mypaystack++)
	{
		if (*myneed != *mypaystack)
			return (NULL);
	}
	return ((char *)mypaystack);
}
/**
 * my_strcat - concatenates two strings
 * @destin: destination buffer
 * @source: source buffer
 * Return: pointer to the destination buffer
 */
char *my_strcat(char *destin, char *source)
{
	char *reting = destin;

	while (*destin)
	{
		destin++;
	}

	for (; *source; source++)
	{
		*destin = *source;
		destin++;
	}

	*destin = *source;

	return (reting);
}

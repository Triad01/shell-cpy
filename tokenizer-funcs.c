#include "shell.h"
/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtor(char *str, char *d);
char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (!str || !str[0])
		return NULL;

	if (!d)
		d = " ";

	i = 0;
	while (str[i] != '\0')
	{
		char current = str[i];
		switch (current)
		{
			case '\0':
				break;

			case ' ':
			case '\t':
			case '\n':
				while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
					i++;
				break;

			default:
				numwords++;
				while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0')
					i++;
				break;
		}
	}

	if (numwords == 0)
		return NULL;

	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return NULL;

	i = 0;
	j = 0;
	while (j < numwords)
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;

		k = 0;
		while (str[i + k] != ' ' && str[i + k] != '\t' && str[i + k] != '\n' && str[i + k] != '\0')
			k++;

		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return NULL;
		}

		for (m = 0; m < k; m++)
			s[j][m] = str[i++];

		s[j][m] = '\0';
		j++;
	}

	s[j] = NULL;
	return s;
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimiter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i = 0, j = 0, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);

	while (str[i] != '\0')
	{
		switch (str[i])
		{
			case d:
				if (str[i + 1] != d)
				{
					numwords++;
				}
				break;
			default:
				if (str[i] != d && !str[i + 1])
				{
					numwords++;
				}
				break;
		}
		i++;
	}

	if (numwords == 0)
		return (NULL);

	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	i = 0;
	j = 0;

	while (j < numwords)
	{
		while (str[i] == d && str[i] != d)
		{
			i++;
		}

		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
		{
			k++;
		}

		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		m = 0;

		while (m < k)
		{
			s[j][m] = str[i++];
			m++;
		}

		s[j][m] = 0;
		j++;
	}

	s[j] = NULL;

	return s;
}

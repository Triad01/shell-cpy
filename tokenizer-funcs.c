#include "shell.h"
/**
 * **mystrtow - splits a string into words.
 * @s: the input string
 * @dy: the delimeter
 * Return: a pointer to an array of strings
 */

char **mystrtow(char *s, char *dy);
char **mystrtow(char *s, char *dy)
{
	int in, jn, kn, mn, mynumwords = 0;
	char **sn;

	if (!s || !s[0])
		return (NULL);

	if (!dy)
		dy = " ";

	in = 0;
	while (s[in] != '\0')
	{
		char mycurrent = s[in];

		switch (mycurrent)
		{
			case '\0':
				break;

			case ' ':
			case '\t':
			case '\n':
				while (s[in] == ' ' || s[in] == '\t' || s[in] == '\n')
					in++;
				break;

			default:
				mynumwords++;
				while (s[in] != ' ' && s[in] != '\t' && s[in] != '\n' && s[in] != '\0')
					in++;
				break;
		}
	}

	if (mynumwords == 0)
		return (NULL);

	sn = malloc((1 + mynumwords) * sizeof(char *));
	if (!sn)
		return (NULL);

	in = 0;
	jn = 0;
	while (jn < mynumwords)
	{
		while (s[in] == ' ' || s[in] == '\t' || s[in] == '\n')
			in++;

		kn = 0;
		while (s[in + kn] != ' ' && s[in + kn] != '\t'
			&& s[in + kn] != '\n' && s[in + kn] != '\0')
			kn++;

		sn[jn] = malloc((kn + 1) * sizeof(char));
		if (!sn[jn])
		{
			for (kn = 0; kn < jn; kn++)
				free(sn[kn]);
			free(sn);
			return (NULL);
		}

		for (mn = 0; mn < kn; mn++)
			sn[jn][mn] = s[in++];

		sn[jn][mn] = '\0';
		jn++;
	}

	sn[jn] = NULL;
	return (sn);
}
/**
 * **mystrtow2 - splits a string into words
 * @stry: the input string
 * @dy: the delimeter
 * Return: a pointer to an array of strings
*/
char **mystrtow2(char *stry, char dy)
{
	int in, jn, kn, mn, mynumwords = 0;
	char **sn;

	if (stry == NULL || stry[0] == 0)
		return (NULL);
	for (in = 0; stry[in] != '\0'; in++)
		if ((stry[in] != dy && stry[in + 1] == dy) ||
			(stry[in] != dy && !stry[in + 1]) || stry[in + 1] == dy)
			mynumwords++;
	if (mynumwords == 0)
		return (NULL);
	sn = malloc((1 + mynumwords) * sizeof(char *));
	if (!sn)
		return (NULL);
	for (in = 0, jn = 0; jn < mynumwords; jn++)
	{
		while (stry[in] == dy && stry[in] != dy)
			in++;
		kn = 0;
		while (stry[in + kn] != dy && stry[in + kn] && stry[in + kn] != dy)
			kn++;
		sn[jn] = malloc((kn + 1) * sizeof(char));
		if (!sn[jn])
		{
			for (kn = 0; kn < jn; kn++)
				free(sn[kn]);
			free(sn);
			return (NULL);
		}
		for (mn = 0; mn < kn; mn++)
			sn[jn][mn] = stry[in++];
		sn[jn][mn] = 0;
	}
	sn[jn] = NULL;
	return (sn);
}

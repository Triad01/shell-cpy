#include "shell.h"

char **mystrtow(char *stry, char *dy)
{
	int in, jn, kn, mn, mynumwords = 0;
	char **sn;

	if (!stry || !stry[0])
		return (NULL);

	if (!dy)
		dy = " ";

	in = 0;
	while (stry[in] != '\0')
	{
		char mycurrent = stry[in];
		switch (mycurrent)
		{
			case '\0':
				break;

			case ' ':
			case '\t':
			case '\n':
				while (stry[in] == ' ' || stry[in] == '\t' || stry[in] == '\n')
					in++;
				break;

			default:
				mynumwords++;
				while (stry[in] != ' ' && stry[in] != '\t' && stry[in] != '\n' && stry[in] != '\0')
					in++;
				break;
		}
	}

	if (mynumwords == 0)
		return (NULL);

	sn = malloc((1 + mynumwords) * sizeof(char *));
	if (!sn)
		return NULL;

	in = 0;
	jn = 0;
	while (jn < mynumwords)
	{
		while (stry[in] == ' ' || stry[in] == '\t' || stry[in] == '\n')
			in++;

		kn = 0;
		while (stry[in + kn] != ' ' && stry[in + kn] != '\t' && stry[in + kn] != '\n' && stry[in + kn] != '\0')
			kn++;

		sn[jn] = malloc((kn + 1) * sizeof(char));
		if (!sn[jn])
		{
			for (kn = 0; kn < jn; kn++)
				free(sn[kn]);
			free(sn);
			return NULL;
		}

		for (mn = 0; mn < kn; mn++)
			sn[jn][mn] = stry[in++];

		sn[jn][mn] = '\0';
		jn++;
	}

	sn[jn] = NULL;
	return sn;
}

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

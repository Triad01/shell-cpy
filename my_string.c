#include "shell.h"

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

char *my_startswith(const char *mypaystack, const char *myneed)
{
	for (; *myneed; myneed++, mypaystack++)
	{
		if (*myneed != *mypaystack)
			return (NULL);
	}
	return ((char *)mypaystack);
}

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

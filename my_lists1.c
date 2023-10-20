#include "shell.h"

size_t my_listlen(const list_t *hd)
{
	size_t a = 0;

	for (; hd; hd = hd->nexts)
	{
		a++;
	}

	return (a);
}

char **my_listtostrings(list_t *hd)
{
	list_t *noder = hd;
	size_t a = my_listlen(hd), b;
	char **strcs;
	char *stri;

	if (!hd || !a)
		return (NULL);

	strcs = malloc(sizeof(char *) * (a + 1));
	if (!strcs)
		return (NULL);

	a = 0;
	do
	{
		stri = malloc(_strlen(noder->string) + 1);
		if (!stri)
		{
			for (b = 0; b < a; b++)
				free(strcs[b]);
			free(strcs);
			return (NULL);
		}

		stri = my_strcpy(stri, noder->string);
		strcs[a] = stri;
		noder = noder->nexts;
		a++;
	} while (noder);

	strcs[a] = NULL;
	return (strcs);
}

size_t my_printlist(const list_t *hd)
{
	size_t a = 0;

	if (!hd)
		return (a);

	do
	{
		my_puts(my_convertnumber(hd->number, 10, 0));
		my_putchar(':');
		my_putchar(' ');
		my_puts(hd->string ? hd->string : "(nil)");
		my_puts("\n");
		hd = hd->nexts;
		a++;
	} while (hd);

	return (a);
}

list_t *my_nodestartswith(list_t *noder, char *pref, char cha)
{
	char *point = NULL;

	if (!noder)
		return NULL;

	do
	{
		point = my_startswith(noder->string, pref);
		if (point && ((cha == -1) || (*point == cha)))
			return noder;
		noder = noder->nexts;
	} while (noder);

	return (NULL);
}

ssize_t my_getnodeindex(list_t *hd, list_t *noder)
{
	size_t a = 0;

	for (; hd; hd = hd->nexts, a++)
	{
		if (hd == noder)
			return (a);
	}

	return (-1);
}

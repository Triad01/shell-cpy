#include "shell.h"
/**
 * my_listlen - checks length of of a singly linked list
 * @hd: pointer to the first node in the list
 * Return: size of list
 */
size_t my_listlen(const list_t *hd)
{
	size_t a = 0;

	for (; hd; hd = hd->nexts)
	{
		a++;
	}

	return (a);
}
/**
 * my_listtostrings - returns an array of strings of the linked list
 * @hd: pointer to the first node in the list
 * Return: always an character array of strings
 */
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
	do {
		stri = malloc(my_strlen(noder->string) + 1);
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
/**
 * my_printlist - prints all the elements of a list_t linked list
 * @hd: A pointer to first node
 * Return: signed integer
 */
size_t my_printlist(const list_t *hd)
{
	size_t a = 0;

	if (!hd)
		return (a);

	do {
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
/**
 * my_nodestartswith - returns node whose starting as prefix
 * @noder: pointer to list head
 * @pref: string to be matched
 * @cha: the next char after prefix to be matched
 * Return: match node of list_t data type
 */
list_t *my_nodestartswith(list_t *noder, char *pref, char cha)
{
	char *point = NULL;

	if (!noder)
		return (NULL);

	do {
		point = my_startswith(noder->string, pref);
		if (point && ((cha == -1) || (*point == cha)))
			return (noder);
		noder = noder->nexts;
	} while (noder);

	return (NULL);
}
/**
 * my_getnodeindex - gets the index of a particular node
 * @hd: pointer to list head
 * @noder: pointer to the node
 * Return: index of node -1 (signed integer)
 */
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

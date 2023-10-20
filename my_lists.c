#include "shell.h"

list_t *myaddnode(list_t **hd, const char *string, int nums)
{
	if (!hd)
		return (NULL);

	list_t *mynewhead = malloc(sizeof(list_t));
	if (!mynewhead)
		return (NULL);

	my_memset((void *)mynewhead, 0, sizeof(list_t));
	mynewhead->number = nums;

	if (string)
	{
		mynewhead->string = my_strdup(string);
		if (!mynewhead->string)
		{
			free(mynewhead);
			return (NULL);
		}
	}

	mynewhead->nexts = *hd;
	*hd = mynewhead;

	return (mynewhead);
}

list_t *my_addnodeend(list_t **hd, const char *strings, int nums)
{
	list_t *mynewnode, *noder;

	if (!hd)
		return (NULL);

	noder = *hd;
	mynewnode = malloc(sizeof(list_t));
	if (!mynewnode)
		return (NULL);
	my_memset((void *)mynewnode, 0, sizeof(list_t));
	mynewnode->number = nums;
	if (strings)
	{
		mynewnode->string = my_strdup(strings);
		if (!mynewnode->string)
		{
			free(mynewnode);
			return (NULL);
		}
	}
	if (noder)
	{
		while (noder->nexts)
			noder = noder->nexts;
		noder->nexts = mynewnode;
	}
	else
		*hd = mynewnode;
	return (mynewnode);
}

size_t my_printliststr(const list_t *had)
{
	size_t a = 0;

	for (; had; had = had->nexts)
	{
		mu_puts(had->string ? had->string : "(nil)");
		my_puts("\n");
		a++;
	}

	return (a);
}

int my_delete(list_t **hd, unsigned int ind)
{
	list_t *noder, *myprev_noder = NULL;
	unsigned int a;

	if (!hd || !*hd)
		return (0);

	if (ind == 0)
	{
		noder = *hd;
		*hd = (*hd)->nexts;
		free(noder->string);
		free(noder);
		return (1);
	}

	noder = *hd;
	for (a = 0; noder && a < ind; a++)
	{
		myprev_noder = noder;
		noder = noder->nexts;
	}

	if (noder)
	{
		myprev_noder->nexts = noder->nexts;
		free(noder->string);
		free(noder);
		return (1);
	}

	return (0);
}

void my_freelist(list_t **hd_pt)
{
	list_t *noder, *mynext_noder, *myhd;

	if (!hd_pt || !*hd_pt)
		return;
	myhd = *hd_pt;

	for (noder = myhd; noder != NULL; noder = mynext_noder)
	{
		mynext_noder = noder->nexts;
		free(noder->string);
		free(noder);
	}

	*hd_pt = NULL;
}

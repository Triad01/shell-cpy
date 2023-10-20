#include "shell.h"

int my_myhistory(info_t *inf)
{
	my_printlist(inf->my_history);
	return (0);
}

int my_unsetalias(info_t *inf, char *strings)
{
	char *point = strings;
	int real;

	while (*point)
	{
		switch (*point)
		{
			case '=':
				*point = '\0';
				real = my_delete(&(inf->my_alias),
								 my_getnodeindex(inf->my_alias, my_nodestartswith(inf->my_alias, strings, -1)));
				*point = '=';
				return real;
			default:
				point++;
		}
	}

	return (1);
}

int my_setalias(info_t *inf, char *strings)
{
	char *point = strings;
	int real = 0;
	char a;

	while (*point)
	{
		switch (*point)
		{
			case '=':
				a = *point;
				*point = '\0';
				if (!*++point)
					real = my_unsetalias(inf, strings);
				else
				{
					my_unsetalias(inf, strings);
					real = (my_addnodeend(&(inf->my_alias), strings, 0) == NULL);
				}
				*point = a;
				return real;
			default:
				point++;
		}
	}

	return (1);
}

int my_printalias(list_t *noders)
{
	char *point, *b;

	if (noders)
	{
		point = my_strchr(noders->string, '=');
		for (b = noders->string; b <= point; b++)
			my_putchar(*b);
		my_putchar('\'');
		my_puts(point + 1);
		my_puts("'\n");
		return (0);
	}
	return (1);
}

int my_myalias(info_t *inf)
{
	int a = 1;
	char *point = NULL;

	if (inf->my_argc == 1)
	{
		list_t *noder = inf->my_alias;
		while (noder)
		{
			my_printalias(noder);
			noder = noder->nexts;
		}
		return (0);
	}

	while (inf->my_argv[a])
	{
		point = my_strchr(inf->my_argv[a], '=');

		if (point)
		{
			my_setalias(inf, inf->my_argv[a]);
		}
		else
		{
			list_t *my_alias_noder = my_nodestartswith(inf->my_alias, inf->my_argv[a], '=');
			if (my_alias_noder)
			{
				my_printalias(my_alias_noder);
			}
		}
		a++;
	}

	return (0);
}


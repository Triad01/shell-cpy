#include "shell.h"
/**
 * my_myhistory - displays the history list
 * @inf: Structure contains arguments.
 *  Return: Always an integer
 */
int my_myhistory(info_t *inf)
{
	my_printlist(inf->my_history);
	return (0);
}
/**
 * my_unsetalias - removes alias to a string
 * @inf: parameter
 * @strings: the string alias
 * Return: Always an integer
 */
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
				return (real);
			default:
				point++;
		}
	}

	return (1);
}
/**
 * my_setalias - sets alias to string
 * @inf: parameter
 * @strings: the string alias
 * Return: Always an integer
 */
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
				return (real);
			default:
				point++;
		}
	}

	return (1);
}
/**
 * my_printalias - prints an alias string to stdout
 * @noders: the alias node
 * Return: Always an integer
 */
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
/**
 * my_myalias - creates an alias
 * @inf: Structure containing potential arguments
 *  Return: Always an integer
 */
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
			list_t *my_alias_noder;

			my_alias_noder = my_nodestartswith(inf->my_alias, inf->my_argv[a], '=');

			if (my_alias_noder)
			{
				my_printalias(my_alias_noder);
			}
		}
		a++;
	}

	return (0);
}

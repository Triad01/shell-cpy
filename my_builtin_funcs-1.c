#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}
/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p = str;
	int ret;

	while (*p)
	{
		switch (*p)
		{
			case '=':
				*p = '\0';
				ret = delete_node_at_index(&(info->alias),
						get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
				*p = '=';
				return ret;
			default:
				p++;
		}
	}

	return 1;
}
/**
 * set_alias - sets an alias to a string
 * @info: the parameter struct
 * @str: the string alias
 *
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p = str;
	int ret = 0;
	char c;

	while (*p)
	{
		switch (*p)
		{
			case '=':
				c = *p;
				*p = '\0';
				if (!*++p)
					ret = unset_alias(info, str);
				else
				{
					unset_alias(info, str);
					ret = (add_node_end(&(info->alias), str, 0) == NULL);
				}
				*p = c;
				return ret;
			default:
				p++;
		}
	}

	return 1;
}
/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p, *a;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return 0;
	}
	return 1;
}
/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 1;  // Start from the second argument (argv[1])
	char *p = NULL;

	if (info->argc == 1)
	{
		list_t *node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return 0;
	}

	while (info->argv[i])
	{
		p = _strchr(info->argv[i], '=');

		if (p)
		{
			set_alias(info, info->argv[i]);
		}
		else
		{
			list_t *alias_node = node_starts_with(info->alias, info->argv[i], '=');
			if (alias_node)
			{
				print_alias(alias_node);
			}
		}
		i++;
	}

	return 0;
}


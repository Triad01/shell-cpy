#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;
	char currentChar = buf[j];

	switch (currentChar)
	{
		case '|':
			if (buf[j + 1] == '|')
			{
				buf[j] = 0;
				j++;
				info->cmd_buf_type = CMD_OR;
			}
			break;
		case '&':
			if (buf[j + 1] == '&')
			{
				buf[j] = 0;
				j++;
				info->cmd_buf_type = CMD_AND;
			}
			break;
		case ';':
			buf[j] = 0;
			info->cmd_buf_type = CMD_CHAIN;
			break;
		default:
			return 0;
	}

	*p = j;
	return 1;
}

/**
 * check_chain - checks if we should continue chaining based on the last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of the current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	switch (info->cmd_buf_type)
	{
		case CMD_AND:
			if (info->status)
			{
				buf[i] = 0;
				j = len;
			}
			break;
		case CMD_OR:
			if (!info->status)
			{
				buf[i] = 0;
				j = len;
			}
			break;
	}

	*p = j;
}

/**
 * replace_alias - replaces aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i = 0;
	list_t *node;
	char *p;

	do
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return 0;

		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return 0;

		p = _strdup(p + 1);
		if (!p)
			return 0;

		info->argv[0] = p;
		i++;
	} while (i < 10);

	return 1;
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	while (info->argv[i])
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
		{
			i++;
			continue;
		}

		switch (info->argv[i][1])
		{
			case '?':
				replace_string(&(info->argv[i]),
						_strdup(convert_number(info->status, 10, 0)));
				break;
			case '$':
				replace_string(&(info->argv[i]),
						_strdup(convert_number(getpid(), 10, 0)));
				break;
			default:
				node = node_starts_with(info->env, &(info->argv[i][1]), '=');
				if (node)
				{
					replace_string(&(info->argv[i]),
							_strdup(_strchr(node->str, '=') + 1));
				}
				else
				{
					replace_string(&(info->argv[i]), _strdup(""));
				}
		}

		i++;
	}

	return 0;
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

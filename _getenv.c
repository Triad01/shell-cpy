#include "shell.h"
/**
 * get_environ - returns the string array copy of the environment list
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: String array of environment variables.
 */
char **get_environ(info_t *info)
{
	// Always update the environment list from info->env
	info->environ = list_to_strings(info->env);

	return info->environ;
}
/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	if (!info->env || !var)
		return 0;

	size_t i = 0;
	list_t *node = info->env;
	char *p;

	for (i = 0; node; node = node->next, i++)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
		}
	}

	return info->env_changed;
}
/**
 * _setenv - Initialize a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	char *p;

	if (!var || !value)
		return 0;

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return 1;
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);

	list_t *node = info->env;

	for (size_t i = 0; node; node = node->next, i++)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return 0;
		}
	}

	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return 0;
}


#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}
#include "shell.h"

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments.
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	for (; node; node = node->next) {
		p = starts_with(node->str, name);
		if (p && *p) {
			return p;
		}
	}

	return NULL;
}
#include "shell.h"

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _mysetenv(info_t *info)
{
	switch (info->argc) {
		case 3:
			if (_setenv(info, info->argv[1], info->argv[2])) {
				return 0;
			} else {
				return 1;
			}
			break;
		default:
			_eputs("Incorrect number of arguments\n");
			return 1;
	}
}
#include "shell.h"

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int i = 1;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return 1;
	}

	while (i <= info->argc)
	{
		_unsetenv(info, info->argv[i]);
		i++;
	}

	return 0;
}
#include "shell.h"

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i = 0;

	do {
		add_node_end(&node, environ[i], 0);
		i++;
	} while (environ[i]);

	info->env = node;
	return 0;
}

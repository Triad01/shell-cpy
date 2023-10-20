#include "shell.h"
/**
 * my_getenvironment - entry
 * @inf: infomate
 * Return: xtruct
 */
char **my_getenvironment(info_t *inf)
{
	inf->my_envir = my_listtostrings(inf->my_env);

	return (inf->my_envir);
}
/**
 * my_unsetenv - entry
 * @myvarable: variable
 * @inf: info
 * Return: 0 or 1
 */
int my_unsetenv(info_t *inf, char *myvarable)
{
	size_t o;
	char *p;
	list_t *noder;

	if (!inf->my_env || !myvarable)
		return (0);


	if (!inf->my_env || !myvarable)
		return (0);

	noder = inf->my_env;

	for (o = 0; noder; noder = noder->nexts, o++)
	{
		p = my_startswith(noder->string, myvarable);
		if (p && *p == '=')
		{
			inf->myenv_change = my_delete(&(inf->my_env), o);
			o = 0;
			noder = inf->my_env;
		}
	}

	return (inf->myenv_change);
}
/**
 * my_setenv - entry
 * @inf: info
 * @variable: variables
 * @valueable: valuable
 * Return: 0 or 1
 */
int my_setenv(info_t *inf, char *variable, char *valueable)
{
	char *buffer = NULL;
	char *point;
	size_t o;
	list_t *noder;

	if (!variable || !valueable)
		return (0);

	buffer = malloc(my_strlen(variable) + my_strlen(valueable) + 2);
	if (!buffer)
		return (1);
	my_strcpy(buffer, variable);
	my_strcat(buffer, "=");
	my_strcat(buffer, valueable);

	noder = inf->my_env;

	for (o = 0; noder; noder = noder->nexts, o++)
	{
		point = my_startswith(noder->string, variable);
		if (point && *point == '=')
		{
			free(noder->string);
			noder->string = buffer;
			inf->myenv_change = 1;
			return (0);
		}
	}

	my_addnodeend(&(inf->my_env), buffer, 0);
	free(buffer);
	inf->myenv_change = 1;
	return (0);
}

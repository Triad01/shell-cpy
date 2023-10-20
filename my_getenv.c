#include "shell.h"

char **my_getenviroment(info_t *inf)
{
	inf->my_envir = my_listtostrings(inf->my_env);

	return inf->my_envir;
}

int my_unsetenv(info_t *inf, char *myvarable)
{
	if (!inf->my_env || !myvarable)
		return (0);

	size_t o = 0;
	list_t *noder = inf->my_env;
	char *p;

	for (o = 0; noder; noder = noder->nexts, o++)
	{
		p = my_startwith(noder->string, myvarable);
		if (p && *p == '=')
		{
			inf->myenv_change = my_delete(&(inf->my_env), o);
			o = 0;
			noder = inf->my_env;
		}
	}

	return inf->myenv_change;
}

int my_setenver(info_t *inf, char *variable, char *valueable)
{
	char *buffer = NULL;
	char *point;

	if (!variable || !valueable)
		return (0);

	buffer = malloc(my_strlen(variable) + my_strlen(valueable) + 2);
	if (!buffer)
		return (1);
	my_strcpy(buffer, variable);
	my_strcat(buffer, "=");
	my_strcat(buffer, valueable);

	list_t *noder = inf->my_env;

	for (size_t o = 0; noder; noder = noder->nexts, o++)
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
	return 0;
}
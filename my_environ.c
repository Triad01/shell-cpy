#include "shell.h"

int my_myenv(info_t *inf)
{
	my_printliststr(inf->my_env);
	return (0);
}

char *my_getenv(info_t *inf, const char *nam)
{
	list_t *noder = inf->my_env;
	char *point;

	for (; noder; noder = noder->nexts)
	{
		point = my_startswith(noder->string, nam);
		if (point && *point)
		{
			return point;
		}
	}

	return NULL;
}

int my_mysetenv(info_t *inf)
{
	switch (inf->my_argc)
	{
	case 3:
		if (my_setenv(inf, inf->my_argv[1], inf->my_argv[2]))
		{
			return (0);
		}
		else
		{
			return (1);
		}
		break;
	default:
		my_eputs("Incorrect number of arguments\n");
		return (1);
	}
}

int my_myunsetenv(info_t *inf)
{
	int a = 1;

	if (inf->my_argc == 1)
	{
		my_eputs("Too few arguments.\n");
		return (1);
	}

	while (a <= inf->my_argc)
	{
		my_unsetenv(inf, inf->my_argv[a]);
		a++;
	}

	return (0);
}

int my_populateenvlist(info_t *inf)
{
	list_t *noder = NULL;
	size_t a = 0;

	do {
		my_addnodeend(&noder, environ[a], 0);
		a++;
	} while (environ[a]);

	inf->my_env = noder;
	return (0);
}

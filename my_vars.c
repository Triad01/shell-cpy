#include "shell.h"

int my_ischain(info_t *infos, char *buffs, size_t *pin)
{
	size_t a = *pin;
	char my_currentChar = buffs[a];

	switch (my_currentChar)
	{
		case '|':
			if (buffs[a + 1] == '|')
			{
				buffs[a] = 0;
				a++;
				infos->cmdtype = MYCMDOR;
			}
			break;
		case '&':
			if (buffs[a + 1] == '&')
			{
				buffs[a] = 0;
				a++;
				infos->cmdtype = MYCMDAND;
			}
			break;
		case ';':
			buffs[a] = 0;
			infos->cmdtype = MYCMDCHAIN;
			break;
		default:
			return (0);
	}

	*pin = a;
	return (1);
}

void my_checkchain(info_t *inf, char *buffs, size_t *pin, size_t in, size_t length)
{
	size_t a = *pin;

	switch (inf->cmdtype)
	{
	case MYCMDAND:
		if (inf->my_status)
		{
			buffs[in] = 0;
			a = length;
		}
		break;
	case MYCMDOR:
		if (!inf->my_status)
		{
			buffs[in] = 0;
			a = length;
		}
		break;
	}

	*pin = a;
}

int my_replacealias(info_t *inf)
{
	int in = 0;
	list_t *noder;
	char *pin;

	do
	{
		noder = my_nodestartswith(inf->my_alias, inf->my_argv[0], '=');
		if (!noder)
			return (0);

		free(inf->my_argv[0]);
		pin = my_strchr(noder->string, '=');
		if (!pin)
			return (0);

		pin = my_strdup(pin + 1);
		if (!pin)
			return (0);

		inf->my_argv[0] = pin;
		in++;
	} while (in < 10);

	return (1);
}

int my_replacevars(info_t *infos)
{
	int in = 0;
	list_t *noder;

	while (infos->my_argv[in])
	{
		if (infos->my_argv[in][0] != '$' || !infos->my_argv[in][1])
		{
			in++;
			continue;
		}

		switch (infos->my_argv[in][1])
		{
		case '?':
			my_replacestring(&(infos->my_argv[in]),
							 my_strdup(my_convertnumber(infos->my_status, 10, 0)));
			break;
		case '$':
			my_replacestring(&(infos->my_argv[in]),
							 my_strdup(my_convertnumber(getpid(), 10, 0)));
			break;
		default:
			noder = my_nodestartswith(infos->my_env, &(infos->my_argv[in][1]), '=');
			if (noder)
			{
				my_replacestring(&(infos->my_argv[in]),
								 my_strdup(my_strchr(noder->string, '=') + 1));
			}
			else
			{
				my_replacestring(&(infos->my_argv[in]), my_strdup(""));
			}
		}

		in++;
	}

	return (0);
}

int my_replacestring(char **older, char *newer)
{
	free(*older);
	*older = newer;
	return (1);
}

#include "shell.h"

void my_clearinfo(info_t *inf)
{
	inf->argsm = NULL;
	inf->my_argv = NULL;
	inf->my_path = NULL;
	inf->my_argc = 0;
}

void my_setinfo(info_t *inf, char **avs)
{
	int a = 0;

	inf->my_f_name = avs[0];
	if (inf->argsm)
	{
		inf->my_argv = strtow(inf->argsm, " \t");
		if (!inf->my_argv)
		{
			inf->my_argv = malloc(sizeof(char *) * 2);
			if (inf->my_argv)
			{
				inf->my_argv[0] = _strdup(inf->argsm);
				inf->my_argv[1] = NULL;
			}
		}

		while (inf->my_argv && inf->my_argv[a])
		{
			a++;
		}
		inf->my_argc = a;

		switch (my_replacealias(inf))
		{
			case 0:
				switch (my_replacevars(inf))
				{
					case 0:
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
}

void my_freeinfo(info_t *inf, int al)
{
	ffree(inf->my_argv);
	inf->my_argv = NULL;
	inf->my_path = NULL;

	switch (al)
	{
		case 1:
			if (!inf->mycmduf)
				free(inf->argsm);
			if (inf->my_env)
				my_freelist(&(inf->my_env));
			if (inf->my_history)
				my_freelist(&(inf->my_history));
			if (inf->my_alias)
				my_freelist(&(inf->my_alias));
			my_ffree(inf->my_envir);
			inf->my_envir = NULL;
			bfree((void **)inf->mycmduf);
			if (inf->reader > 2)
				close(inf->reader);
			_putchar(MYBUFLUSH);
			break;
		default:
			break;
	}
}

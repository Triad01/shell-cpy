#include "shell.h"

int my_myexit(info_t *inf)
{
	int exit;
	int check = -2;

	switch (inf->my_argv[1] ? 1 : 0)
	{
	case 1:
		exit = my_erratoi(inf->my_argv[1]);
		if (exit == -1)
		{
			inf->my_status = 2;
			my_printerror(inf, "unacceptable number: ");
			my_eputs(inf->my_argv[1]);
			my_eputchar('\n');
			check = 1;
		}
		else
		{
			inf->my_errnum = exit;
			check = -2;
		}
		break;
	case 0:
		inf->my_errnum = -1;
		check = -2;
		break;
	}

	return (check);
}

int my_mycd(info_t *inf)
{
	char *sy, *direct, mybuffer[1024];
	int chdireset;
	int check = 0;

	sy = getcwd(mybuffer, 1024);
	if (!sy)
		my_puts("TODO: Handle getcwd failure here\n");

	switch (inf->my_argv[1] ? 1 : (inf->my_argv[1] && my_strcmp(inf->my_argv[1], "-") == 0) ? 2
																							: 0)
	{
		case 1:
			direct = my_getenv(inf, "HOME=");
			if (!direct)
				chdireset = chdir((direct = my_getenv(inf, "PWD=")) ? direct : "/");
			else
				chdireset = chdir(direct);
			break;

		case 2:
			if (!my_getenv(inf, "OLDPWD="))
			{
				my_puts(sy);
				my_putchar('\n');
				check = 1;
			}
			else
			{
				my_puts(my_getenv(inf, "OLDPWD="));
				my_putchar('\n');
				chdireset = chdir((direct = my_getenv(inf, "OLDPWD=")) ? direct : "/");
			}
			break;

		default:
			chdireset = chdir(inf->my_argv[1]);
			break;
	}

	if (chdireset == -1)
	{
		my_printerror(inf, "can't cd to ");
		my_eputs(inf->my_argv[1]);
		my_eputchar('\n');
	}
	else
	{
		my_setenv(inf, "OLDPWD", my_getenv(inf, "PWD="));
		my_setenv(inf, "PWD", getcwd(mybuffer, 1024));
	}

	return (check);
}

int my_myhelp(info_t *inf)
{
	char **my_argarray;

	my_argarray = inf->my_argv;
	my_puts("Help function is not yet implemented.\n");

	switch (0) {
		case 0:
			my_puts(*my_argarray);
			break;
		default:
			break;
	}

	return (0);
}

#include "shell.h"
/**
 * my_myexit - exits the shell completly
 * @inf: Structure containing arguments.
 * Return: always an integer
 */

int my_myexit(info_t *inf);
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
/**
 * my_mycd - changes the current directory of the process
 * @inf: Structure containing arguments
 * Return: Always an integer
 */
int my_mycd(info_t *inf)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		my_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->my_argv[1])
	{
		dir = my_getenv(inf, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = my_getenv(inf, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (my_strcmp(inf->my_argv[1], "-") == 0)
	{
		if (!my_getenv(inf, "OLDPWD="))
		{
			my_puts(s);
			my_putchar('\n');
			return (1);
		}
		my_puts(my_getenv(inf, "OLDPWD=")), my_putchar('\n');
		chdir_ret = chdir((dir = my_getenv(inf, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(inf->my_argv[1]);
	if (chdir_ret == -1)
	{
		my_printerror(inf, "can't cd to ");
		my_eputs(inf->my_argv[1]), my_eputchar('\n');
	}
	else
	{
		my_setenv(inf, "OLDPWD", my_getenv(inf, "PWD="));
		my_setenv(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * my_myhelp - helper func
 * @inf: containins arguments
 * Return: Always an integer
 */
int my_myhelp(info_t *inf)
{
	char **my_argarray;

	my_argarray = inf->my_argv;
	my_puts("Help function is not yet implemented.\n");

	switch (0)
	{
		case 0:
			my_puts(*my_argarray);
			break;
		default:
			break;
	}

	return (0);
}

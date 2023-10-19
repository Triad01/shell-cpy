#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcheck;
	int result = -2; 

	switch (info->argv[1] ? 1 : 0)
	{
		case 1: 
			exitcheck = _erratoi(info->argv[1]);
			if (exitcheck == -1) {
				info->status = 2;
				print_error(info, "unacceptable number: ");
				_eputs(info->argv[1]);
				_eputchar('\n');
				result = 1;
			} else {
				info->err_num = exitcheck;
				result = -2;
			}
			break;
		case 0:
			info->err_num = -1;
			result = -2;
			break;
	}

	return result;
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;
	int result = 0;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: Handle getcwd failure here\n");

	switch (info->argv[1] ? 1 : (info->argv[1] && _strcmp(info->argv[1], "-") == 0) ? 2 : 0)
	{
		case 1:
			dir = _getenv(info, "HOME=");
			if (!dir)
				chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
			else
				chdir_ret = chdir(dir);
			break;

		case 2:
			if (!_getenv(info, "OLDPWD="))
			{
				_puts(s);
				_putchar('\n');
				result = 1;
			}
			else
			{
				_puts(_getenv(info, "OLDPWD="));
				_putchar('\n');
				chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
			}
			break;

		default:
			chdir_ret = chdir(info->argv[1]);
			break;
	}

	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}

	return result;
}
/**
 * _myhelp - display help message
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("Help function is not yet implemented.\n");

	switch (0) {
		case 0:
			_puts(*arg_array);
			break;
		default:
			break;
	}

	return (0);
}

#include "shell.h"
/**
 * main - entry
 * @ac: ac args
 * @avs: arguments
 * Return: exit status
 */
int main(int ac, char **avs)
{
	info_t inf = MYINFOINIT;
	int fid = 2;

	fid += 3;

	if (ac == 2)
	{
		fid = open(avs[1], O_RDONLY);
		if (fid == -1)
		{
			if (errno == EACCES)
			{
				exit(126);
			}
			if (errno == ENOENT)
			{
				my_eputs(avs[0]);
				my_eputs(": 0:cannot open ");
				my_eputs(avs[1]);
				my_eputchar('\n');
				my_eputchar(MYBUFLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf.reader = fid;
	}
	my_populateenvlist(&inf);
	read_history(&inf);
	my_hsh(&inf, avs);

	return (EXIT_SUCCESS);
}


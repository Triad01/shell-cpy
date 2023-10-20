#include "shell.h"

int my_iscmd(info_t *inf, char *mypath)
{
	struct stat stats;

	(void)inf;

	if (!mypath || my_stat(mypath, &stats))
		return (0);

	switch (stats.st_mode & S_IFMT)
	{
	case S_IFREG:
		return (1);
	default:
		return (0);
	}
}

char *my_dupchars(char *mypathstring, int mystart, int mystop)
{
	static char buffer[1024];
	int in = mystart, ki = 0;

	while (in < mystop)
	{
		if (mypathstring[in] != ':')
		{
			buffer[ki++] = mypathstring[in];
		}
		in++;
	}
	buffer[ki] = 0;
	return (buffer);
}

char *my_findpath(info_t *myinfo, char *mypathstr, char *mycmd)
{
	int a;
	int my_currpos = 0;
	char *mypath = NULL;

	if (!mypathstr)
		return (NULL);
	if ((my_strlen(mycmd) > 2) && my_startswith(mycmd, "./"))
	{
		if (my_iscmd(myinfo, mycmd))
			return (mycmd);
	}

	for (a = 0; mypathstr[a]; a++)
	{
		switch (mypathstr[a])
		{
			case ':':
				mypath = my_dupchars(mypathstr, my_currpos, a);
				if (!*mypath)
					my_strcat(mypath, mycmd);
				else
				{
					my_strcat(mypath, "/");
					my_strcat(mypath, mycmd);
				}

				if (my_iscmd(myinfo, mypath))
					return (mypath);

				my_currpos = a;
				break;
		}
	}
	return (NULL);
}


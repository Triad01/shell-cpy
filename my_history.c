#include "shell.h"
/**
 * my_gethistoryfile - entry
 * @inf: information
 * Return: NULL or BUff
 */
char *my_gethistoryfile(info_t *inf);
char *my_gethistoryfile(info_t *inf)
{
	char *direct = my_getenv(inf, "HOME=");

	if (!direct)
		return (NULL);

	char *buff = malloc(my_strlen(direct) + my_strlen(MYHISTFILE) + 2);

	if (!buff)
		return (NULL);

	my_strcpy(buff, direct);
	my_strcat(buff, "/");
	my_strcat(buff, MYHISTFILE);

	return (buff);
}
/**
 * my_writehistory - entry
 * @inf: infomation
 * Return: 1 or 0
 */
int my_writehistory(info_t *inf)
{
	ssize_t fid;
	char *file_names = my_gethistoryfile(inf);
	list_t *noder = inf->my_history;

	if (!file_names)
		return (-1);

	fid = open(file_names, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_names);

	if (fid == -1)
		return (-1);

	do {
		my_putsfd(noder->string, fid);
		my_putfd('\n', fid);
		noder = noder->nexts;
	} while (noder);

	my_putfd(MYBUFLUSH, fid);
	close(fid);

	return (1);
}
/**
 * read_history - history entry
 * @inf: history information
 * Return: 1 or 0
 */
int read_history(info_t *inf);
int read_history(info_t *inf)
{
	int a, mylast = 0, myline_count = 0;
	ssize_t fid, myrlen, myf_size = 0;
	struct stat stats;
	char *buffer = NULL, *file_names = my_gethistoryfile(inf);

	if (!file_names)
		return (0);

	fid = open(file_names, O_RDONLY);
	free(file_names);
	if (fid == -1)
		return (0);

	if (!fstat(fid, &stats))
		myf_size = stats.st_size;

	if (myf_size < 2)
		return (0);

	buffer = malloc(sizeof(char) * (myf_size + 1));
	if (!buffer)
		return (0);

	myrlen = read(fid, buffer, myf_size);
	buffer[myf_size] = 0;

	if (myrlen <= 0)
	{
		free(buffer);
		return (0);
	}

	close(fid);

	for (a = 0; a < myf_size; a++)
	{
		switch (buffer[a])
		{
			case '\n':
				buffer[a] = 0;
				my_buildhistorylist(inf, buffer + mylast, myline_count++);
				mylast = a + 1;
				break;

			default:
				break;
		}
	}

	if (mylast != a)
	{
		my_buildhistorylist(inf, buffer + mylast, myline_count++);
	}

	free(buffer);
	inf->hcount = myline_count;

	while (inf->hcount-- >= MYHISTMAX)
	{
		my_delete(&(inf->my_history), 0);
	}

	my_renumberhistory(inf);
	return (inf->hcount);
}
/**
 * my_buildhistorylist - entry
 * @inf: info build
 * @buffer: buffer
 * @myline_count: count line
 * Return: 0 or 1
 */
int my_buildhistorylist(info_t *inf, char *buffer, int myline_count)
{
	list_t *noder = inf->my_history;

	my_addnodeend(&noder, buffer, myline_count);

	inf->my_history = noder;

	return (0);
}
/**
 * my_renumberhistory - enter
 * @inf: remmenber info
 * Return: hcount
 */
int my_renumberhistory(info_t *inf)
{
	list_t *noder = inf->my_history;
	int a = 0;

	if (noder)
	{
		do {
			noder->number = a++;
			noder = noder->nexts;
		} while (noder);
	}

	return (inf->hcount = a);
}


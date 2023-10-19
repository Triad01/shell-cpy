#include "shell.h"
/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */
char *get_history_file(info_t *info)
{
	char *dir = _getenv(info, "HOME=");

	if (!dir)
		return NULL;

	char *buf = malloc(_strlen(dir) + _strlen(HIST_FILE) + 2);
	if (!buf)
		return NULL;

	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);

	return buf;
}
/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = info->history;

	if (!filename)
		return -1;

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
		return -1;

	do {
		_putsfd(node->str, fd);
		_putfd('\n', fd);
		node = node->next;
	} while (node);

	_putfd(BUF_FLUSH, fd);
	close(fd);

	return 1;
}
/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return 0;

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return 0;

	if (!fstat(fd, &st))
		fsize = st.st_size;

	if (fsize < 2)
		return 0;

	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return 0;

	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;

	if (rdlen <= 0) {
		free(buf);
		return 0;
	}

	close(fd);

	for (i = 0; i < fsize; i++)
	{
		switch (buf[i])
		{
			case '\n':
				buf[i] = 0;
				build_history_list(info, buf + last, linecount++);
				last = i + 1;
				break;

			default:
				break;
		}
	}

	if (last != i)
	{
		build_history_list(info, buf + last, linecount++);
	}

	free(buf);
	info->histcount = linecount;

	while (info->histcount-- >= HIST_MAX)
	{
		delete_node_at_index(&(info->history), 0);
	}

	renumber_history(info);
	return info->histcount;
}
/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = info->history;

	if (node)
	{
		while (node->next)
		{
			node = node->next;
		}
		node->next = create_node(buf, linecount);
		if (node->next == NULL)
			return (-1);
	}
	else
	{
		info->history = create_node(buf, linecount);
		if (info->history == NULL)
			return (-1);
	}

	return (0);
}
/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	if (node)
	{
		do
		{
			node->num = i++;
			node = node->next;
		} while (node);
	}

	return (info->histcount = i);
}


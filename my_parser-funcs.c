#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;

	if (!path || stat(path, &st))
		return 0;

	switch (st.st_mode & S_IFMT) {
		case S_IFREG:
			return 1;
		default:
			return 0;
	}
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = start, k = 0;

	while (i < stop) {
		if (pathstr[i] != ':') {
			buf[k++] = pathstr[i];
		}
		i++;
	}
	buf[k] = 0;
	return buf;
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int curr_pos = 0;
	char *path = NULL;

	if (!pathstr)
		return NULL;
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return cmd;
	}

	for (int i = 0; pathstr[i]; i++)
	{
		switch (pathstr[i])
		{
			case ':':
				path = dup_chars(pathstr, curr_pos, i);
				if (!*path)
					_strcat(path, cmd);
				else
				{
					_strcat(path, "/");
					_strcat(path, cmd);
				}

				if (is_cmd(info, path))
					return path;

				curr_pos = i;
				break;
		}
	}
	return NULL;
}


#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stddef.h>

/* for read/write buffers */
#define MYREADSIZE 1024
#define MY_WRITEBUFSIZE 1024
#define MYBUFLUSH -1

/* for command chaining */
#define MYCMDSNORMER 0
#define MYCMDOR 1
#define MYCMDAND 2
#define MYCMDCHAIN 3

/* for convert_number() */
#define MY_CONVERTLOWERCASE 1
#define MY_CONVERTUNSIGNED 2

/* 1 if using system getline() */
#define MYUSE_GETLINER 0
#define USE_STRTOK 0

#define MYHISTFILE ".simple_shell_history"
#define MYHISTMAX 4096

extern char **environ;

typedef struct list
{
	int number;
	char *string;
	struct list *nexts;
} list_t;

typedef struct info
{
	char *argsm;
	char **my_argv;
	char *my_path;
	int my_argc;
	unsigned int my_linecount;
	int my_errnum;
	int mylineflag;
	char *my_f_name;
	list_t *my_env;
	list_t *my_history;
	list_t *my_alias;
	char **my_envir;
	int myenv_change;
	int my_status;
	char **mycmduf;
	int cmdtype;
	int reader;
	int hcount;
} info_t;

#define MYINFOINIT                                                              \
	{                                                                           \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0                                                             \
	}

typedef struct mybuiltin
{
	char *type;
	int (*funct)(info_t *);
} mybuiltin_table;

int my_eputchar(char);
int my_putchar(char);
void my_siginthandler(int); /*donot delete*/

#endif


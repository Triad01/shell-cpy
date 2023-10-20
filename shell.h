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

/**
 * struct list - a singly linked list
 * @number: the number field
 * @string: a string
 * @nexts: pointer to the next node
 */
typedef struct list
{
	int number;
	char *string;
	struct list *nexts;
} list_t;
/**
 * struct info - contains arguements to be passed into a function,
 * @argsm: a string gotten from getline
 * @my_argv:an argument variable generated from arg
 * @my_path: a string path for the current command
 * @my_argc: the argument count
 * @my_linecount: the error count
 * @my_errnum: exits error code
 * @mylineflag: if on, it counts the line of input
 * @my_f_name: reps the program filename
 * @my_env: linked list of the local copy of environ
 * @my_envir: custom modified copy of env
 * @my_history: the history node
 * @my_alias: the alias node
 * @myenv_change: if environ was changed, it is on
 * @my_status: the return status of the last executed command
 * @mycmduf: contains address of pointer to cmd_buf
 * @cmdtype: CMD_type ||, &&, ;
 * @reader: the file discriptor
 * @hcount: counts the history line number
 */
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

#define MYINFOINIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0}

/**
 * struct mybuiltin - contains a builtin string and other functions
 * @type: the contained builtin flag
 * @funct: the function
 */
typedef struct mybuiltin
{
	char *type;
	int (*funct)(info_t *);
} mybuiltin_table;

int my_eputchar(char);
int my_putchar(char);
void my_siginthandler(int);
ssize_t my_inputbuffers(info_t *inf, char **buffer, size_t *length);
ssize_t my_getinput(info_t *inf);
ssize_t my_readbuf(info_t *inf, char *buffer, size_t *in);
int my_getline(info_t *inf, char **pointer, size_t *len);
int my_myexit(info_t *inf);
int my_mycd(info_t *inf);
int my_myhelp(info_t *inf);
char *my_strncpy(char *destin, char *source, int num);
char *my_strncat(char *destin, char *source, int num);
char *my_strchr(char *sy, char cy);
char *my_gethistoryfile(info_t *inf);
int my_writehistory(info_t *inf);
int read_history(info_t *inf);
int my_buildhistorylist(info_t *inf, char *buffer, int myline_count);
int my_renumberhistory(info_t *inf);
int my_iscmd(info_t *inf, char *mypath);
char *my_dupchars(char *mypathstring, int mystart, int mystop);
char *my_findpath(info_t *myinfo, char *mypathstr, char *mycmd);
int my_ischain(info_t *infos, char *buffs, size_t *pin);
void my_checkchain(info_t *inf, char *, size_t *pin, size_t in, size_t length);
int my_replacealias(info_t *inf);
int my_replacevars(info_t *infos);
int my_replacestring(char **older, char *newer);
int my_myenv(info_t *inf);
char *my_getenv(info_t *inf, const char *nam);
int my_mysetenv(info_t *inf);
int my_myunsetenv(info_t *inf);
int my_populateenvlist(info_t *inf);
char **my_getenvironment(info_t *inf);
int my_unsetenv(info_t *inf, char *myvarable);
int my_setenv(info_t *inf, char *variable, char *valueable);
list_t *myaddnode(list_t **hd, const char *string, int nums);
list_t *my_addnodeend(list_t **hd, const char *strings, int nums);
size_t my_printliststr(const list_t *had);
int my_delete(list_t **hd, unsigned int ind);
void my_freelist(list_t **hd_pt);
int my_hsh(info_t *inf, char **avs);
int my_findbuiltin(info_t *inf);
void my_findcmd(info_t *inf);
void my_forkcmd(info_t *inf);
char *my_memset(char *sy, char by, unsigned int ny);
void my_ffree(char **pap);
void *my_realloc(void *myptr, unsigned int, unsigned int mynew_size);
int my_interactiveness(info_t *infos);
int my_isdelimeter(char charact, char *delimeter);
int my_alphabet(int input);
int my_atoi(char *strings);
int my_erratoi(char *siz);
void my_printerror(info_t *inf, char *chestr);
int my_printd(int put, int fid);
char *my_convertnumber(long int number, int bases, int flgs);
void my_removecomments(char *buffer);
void my_clearinfo(info_t *inf);
void my_setinfo(info_t *inf, char **avs);
void my_freeinfo(info_t *inf, int al);
size_t my_listlen(const list_t *hd);
char **my_listtostrings(list_t *hd);
size_t my_printlist(const list_t *hd);
list_t *my_nodestartswith(list_t *noder, char *pref, char cha);
ssize_t my_getnodeindex(list_t *hd, list_t *noder);
int my_strlen(char *sh);
int my_strcmp(char *sh1, char *sh2);
char *my_startswith(const char *mypaystack, const char *myneed);
char *my_strcat(char *destin, char *source);
int my_myhistory(info_t *inf);
int my_unsetalias(info_t *inf, char *strings);
int my_setalias(info_t *inf, char *strings);
int my_printalias(list_t *noders);
int my_myalias(info_t *inf);
void my_eputs(char *strings);
int my_eputchar(char cha);
int my_eputchar(char cha);
int my_putfd(char cha, int fid);
int my_putsfd(char *strings, int fid);
ssize_t my_inputbuffers(info_t *inf, char **buffer, size_t *length);
ssize_t my_getinput(info_t *inf);
ssize_t my_readbuf(info_t *inf, char *buffer, size_t *in);
int my_getline(info_t *inf, char **pointer, size_t *len);
void my_sigintHandler(__attribute__((unused)) int mysigum);
int my_bfree(void **pointer);
char *my_strcpy(char *destin, char *source);
char *my_strdup(const char *string);
void my_puts(char *strings);
int my_putchar(char character);
char **mystrtow(char *stry, char *dy);
char **mystrtow2(char *stry, char dy);
#endif


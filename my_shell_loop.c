#include "shell.h"
/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
    ssize_t r;
    int builtin_ret;

    for (r = 0, builtin_ret = 0; r != -1 && builtin_ret != -2; clear_info(info))
    {
        if (interactive(info))
        {
            _puts("$ ");
        }
        _eputchar(BUF_FLUSH);
        r = get_input(info);

        if (r != -1)
        {
            set_info(info, av);
            builtin_ret = find_builtin(info);

            switch (builtin_ret)
            {
                case -1:
                    find_cmd(info);
                    break;
                default:
                    break;
            }
        }
        else if (interactive(info))
        {
            _putchar('\n');
        }
        free_info(info, 0);
    }

    write_history(info);
    free_info(info, 1);

    if (!interactive(info) && info->status)
    {
        exit(info->status);
    }

    switch (builtin_ret)
    {
        case -2:
            if (info->err_num == -1)
            {
                exit(info->status);
            }
            exit(info->err_num);
            break;
        default:
            return builtin_ret;
    }
}
/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
    int i = 0;
    int built_in_ret = -1;
    builtin_table builtintbl[] = {
        {"exit", _myexit},
        {"env", _myenv},
        {"help", _myhelp},
        {"history", _myhistory},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}
    };

    while (builtintbl[i].type)
    {
        if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
        {
            info->line_count++;
            built_in_ret = builtintbl[i].func(info);
            break;
        }
        i++;
    }

    return built_in_ret;
}
/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
    char *path = NULL;
    int i = 0;
    int k = 0;

    switch (info->linecount_flag)
    {
        case 1:
            info->line_count++;
            info->linecount_flag = 0;
            break;
    }

    while (info->arg[i])
    {
        switch (!is_delim(info->arg[i], " \t\n"))
        {
            case 1:
                k++;
                break;
        }
        i++;
    }

    switch (k)
    {
        case 0:
            return;
    }

    path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        fork_cmd(info);
    }
    else
    {
        switch (interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/')
        {
            case 1:
                if (is_cmd(info, info->argv[0]))
                {
                    fork_cmd(info);
                }
                break;
        }

        if (*(info->arg) != '\n')
        {
            info->status = 127;
            print_error(info, "not found\n");
        }
    }
}
/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
    pid_t child_pid;

    switch ((child_pid = fork()))
    {
        case -1:
            perror("Error:");
            return;

        case 0:
            if (execve(info->path, info->argv, get_environ(info)) == -1)
            {
                free_info(info, 1);
                switch (errno)
                {
                    case EACCES:
                        exit(126);
                    default:
                        exit(1);
                }
        
            }
            break;

        default:
            wait(&(info->status));
            if (WIFEXITED(info->status))
            {
                info->status = WEXITSTATUS(info->status);
                switch (info->status)
                {
                    case 126:
                        print_error(info, "Permission denied\n");
                        break;
                }
            }
            break;
    }
}


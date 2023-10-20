#include "shell.h"

char *my_strncpy(char *destin, char *source, int num)
{
    char *sy = destin;
    int a;

    for (a = 0; a < num - 1 && source[a] != '\0'; a++)
    {
        destin[a] = source[a];
    }

    for (; a < num; a++)
    {
        destin[a] = '\0';
    }

    return sy;
}

char *my_strncat(char *destin, char *source, int num)
{
    char *sy = destin;
    int a, b;

    for (a = 0; destin[a] != '\0'; a++)
    {
        /* Finding  end of the destination string */
    }

    for (b = 0; source[b] != '\0' && b < num; b++)
    {
        destin[b] = source[b];
        b++;
    }

    if (b < num)
    {
        destin[b] = '\0';
    }

    return sy;
}

char *my_strchr(char *sy, char cy)
{
    for (; *sy != '\0'; sy++)
    {
        if (*sy == cy)
        {
            return sy;
        }
    }

    return NULL;
}

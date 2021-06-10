/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ...
*/

# include <stdio.h>
# include <stdbool.h>
# include <sys/queue.h>
# include <stdlib.h>
# include "zappy.h"

int print_error(const char *func)
{
    perror(func);
    return (84);
}

// DO NOT CHANGE/INLINE/MACRO/...
int max(int a, int b)
{
    return (a > b ? a : b);
}

int get_word_arr_size(char **arr)
{
    int count = 0;

    for (; arr[count]; count++);
    return (count);
}

char **str_to_word_tab(char *buff, char separator)
{
    char **str;
    int i = 0;
    int j = 0;

    for (; buff && buff[j]; j++)
        if (buff[j] == separator)
            i++;
    str = malloc(sizeof(char *) * (i + 2));
    for (i = 0; str && buff && *buff; i++) {
        for (j = 0; buff[j] && buff[j] != separator; j++);
        str[i] = malloc(sizeof(char) * (j + 1));
        for (j = 0; *buff && *buff != separator; buff++)
            str[i][j++] = *buff;
        str[i][j] = '\0';
        buff = *buff ? buff + 1 : buff;
    }
    if (str)
        str[i] = NULL;
    return (str);
}

#include "../mini_shell.h"

static int matching_starting(char *file_name, char *pattern)
{
    int i;

    i = 0;
    if (pattern[i] != '*')
    {
        while (pattern[i] != '*')
            i++;
        if (ft_strncmp(file_name, pattern, i))
            return (0);
    }
    return (1);
}

static int matching_ending(char *file_name, char *pattern, char *str)
{
    int i;
    int size_str;

    i = ft_strlen(file_name) - 1;
    size_str = ft_strlen(str);
    if (pattern[ft_strlen(pattern) - 1] != '*')
    {
        i = i - (size_str - 1);
        if (i < 0)
            return (0);
        if (ft_strncmp(&file_name[i], str, size_str + 1))
            return (0);
    }
    return (1);
}

char *match(char *file_name, char *pattern)
{
    char **arr;
    char *dummy;
    int i;

    if (!matching_starting(file_name, pattern))
        return (0);
    arr = ft_split(pattern, '*');
    if (!arr)
        return (0);
    if (!arr[0])
        return (free_double(arr), file_name);
    dummy = file_name;
    i = -1;
    while (arr[++i])
    {
        dummy = strstr(dummy, arr[i]);         // ft_strstr;
        if (!dummy)
            return (free_double(arr), NULL);
    }
    if (!matching_ending(file_name, pattern, arr[i - 1]))
        return (free_double(arr), NULL);
    return (free_double(arr), file_name);
}


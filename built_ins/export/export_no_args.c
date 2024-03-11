#include "../../mini_shell.h"

void export_no_args(t_listt *head_env)
{
    char *str;
    char **arr;

    while (head_env)
    {
        str = ft_strchr(head_env->content, '=');
        arr = ft_split(head_env->content, '=');
        if (!arr)
            return (perror("malloc: "));
        if (!str)
            printf("declare -x %s\n", (char *)head_env->content);
        else if (*(str + 1) == '\0')
            printf("declare -x %s\"\"\n", (char *)head_env->content);
        else
            printf("declare -x %s=\"%s\"\n", arr[0], str + 1);
        free_double(arr);
        head_env = head_env->next;
    }
}

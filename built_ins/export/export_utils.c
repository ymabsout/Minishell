#include "../../mini_shell.h"

static void join_env(t_listt *node, char *env_var)
{
    char *final_form;
    char *str;
    char *str2;

    str = ft_strdup(env_var);
    if (!str)
        return ;
    str2 = ft_strchr(node->content, '=');
    if (!str2)
        final_form = ft_strjoin(node->content, ft_strchr(str, '='));
    else
        final_form = ft_strjoin(node->content, ft_strchr(str, '=') + 1);
    if (!final_form)
        return (free(str), perror("malloc: "));
    free(str);
    free(node->content);
    node->content = (void *)final_form;
}

void replace_env(t_listt *node, char *env_var)
{
    char **arr;
    char *str;

    arr = ft_split(env_var, '=');
    if (!arr)
        return (perror("malloc: "));
    if (arr[0][ft_strlen(arr[0]) - 1] == '+')
        return (join_env(node, env_var), free_double(arr));
    free_double(arr);
    str = ft_strdup(env_var);
    if (!str)
        return ;
    free(node->content);
    node->content = (void *)str;
}

void add_env(t_listt **head_env, char *env_var)
{
    t_listt *node;
    char **arr;
    char *str;
    char *str2;
    char *env_v;

    arr = ft_split(env_var, '+');
    if (!arr)
        return (perror("malloc: "));
    str = ft_strdup(env_var);
    if (!str)
        return (free_double(arr), perror("malloc: "));
    str2 = ft_strchr(env_var, '=');
    if (arr[1])
        env_v = ft_strjoin(arr[0], str2);
    else
        env_v = str;
    if (!env_v)
        return (free_double(arr), free(str), perror("malloc: "));
    node = ft_lstnew(env_v);
    if (!node)
        exit(-1);
    ft_lstadd_back(head_env, node);
}

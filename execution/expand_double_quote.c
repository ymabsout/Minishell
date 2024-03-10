#include "../mini_shell.h"

static char *get_my_env(t_listt *envs, char *env_str)
{
    char *wr;

    while (envs)
    {
        wr = ft_strnstr(envs->content, env_str, ft_strlen(env_str));
        if (wr)
            break ;
        envs = envs->next;
    }
    free(env_str);
    if (wr)
        env_str = ft_strdup(ft_strchr(wr, '=') + 1);
    else
        env_str = ft_strdup("");
    return (env_str);
}

static char *expand_env(char *complete_str, \
    char *str, int del, t_listt *envs)
{
    int i;
    char *env;
    char *first_part;
    char *full;
    char *final;

    i = 0;
    while (++i)
        if (!ft_isalnum(str[i]) && str[i] != '_')
            break ;
    first_part = ft_substr(complete_str, 0, del);
    env = ft_substr(str, 1, i - 1);
    env = get_my_env(envs, env);
    full = ft_strjoin(first_part, env);
    free(first_part);
    free(env);
    final = ft_strjoin(full, &str[i]);
    free(full);
    free(complete_str);
    return (final);
}

static char *expand_status_code(char *complete_str, \
    char *str, int del, int status_code)
{
    char *first_part;
    char *half;
    char *code;
    char *full;

    first_part = ft_substr(complete_str, 0, del);
    if (str[1] != '?')
        half = ft_strjoin(first_part, "");
    else
    {
        code = ft_itoa(status_code);
        half = ft_strjoin(first_part, code);
        free(code);
    }
    free(first_part);
    full = ft_strjoin(half, str + 2);
    free(complete_str);
    free(half);
    return (full);
}

static void expand_dollar_sign(t_btree *exec_tree, \
    int status_code, t_listt *env)
{
    int i;

    i = 0;
    while (exec_tree->item[i])
    {
        if (exec_tree->item[i] == '$')
        {
            if (exec_tree->item[i + 1] >= '0' && exec_tree->item[i + 1] <= '9')
                exec_tree->item = expand_status_code(exec_tree->item,\
                    exec_tree->item + i, i, status_code);
            else if (ft_isalpha(exec_tree->item[i + 1]) || \
                exec_tree->item[i + 1] == '_')
                exec_tree->item = expand_env(exec_tree->item,\
                    exec_tree->item + i, i , env);
            else if (exec_tree->item[i + 1] == '?')
                exec_tree->item = expand_status_code(exec_tree->item,\
                    exec_tree->item + i, i, status_code);
            else
                i++;
        }
        else
            i++;
    }
}

void expand_double_quote(t_btree *exec_tree, int status_code, t_listt *env)
{
    char *buffer;

    buffer = ft_strtrim(exec_tree->item, "\"");
    free(exec_tree->item);
    exec_tree->item = buffer;
    expand_dollar_sign(exec_tree, status_code, env);
}
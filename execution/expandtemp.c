#include "../mini_shell.h"

// static char *get_my_env()
// {
//     ∆
// }

static char *expand_env(char *complete_str, char *str, int del, t_listt *envs)
{
    int i;
    char *env;
    char *first_part;
    char *j;
    char  **arr;

    i = 0;
    while (++i)
        if (!ft_isalnum(str[i]) && str[i] != '_')
            break ;
    first_part = ft_substr(complete_str, 0, del);
    env = ft_substr(str, 1, i - 1);
    char *lol;
    while (envs)
    {
        lol = ft_strnstr(envs->content, env, ft_strlen(env));
        if (lol)
            break ;
        envs = envs->next;
    }
    if (!lol)
        env = ft_strdup("");
    else
    {
        arr = ft_split(lol, '=');
        env = ft_strdup(arr[1]);
        free_double(arr);
    }
    j = ft_strjoin(first_part, env);
    char *final = ft_strjoin(j, &str[i]);
    free(complete_str);
    return (final);
}


static char *expand_status_code(char *complete_str, char *str, int del, int status_code)
{
    char *first_part;
    char *half;
    char *code;
    char *full;

    first_part = ft_substr(complete_str, 0, del);
    code = ft_itoa(status_code);
    half = ft_strjoin(first_part, code);
    free(first_part);
    free(code);
    full = ft_strjoin(half, str + 2);
    free(complete_str);
    free(half);
    return (full);
}

static void expand_dollar_sign(t_btree *exec_tree, int status_code, t_listt *env)
{
    int i;

    i = -1;
    while (exec_tree->item[++i])
    {
        if (exec_tree->item[i] == '$')
        {
            if (ft_isalnum(exec_tree->item[i + 1]) || \
                exec_tree->item[i + 1] == '_')
                exec_tree->item = expand_env(exec_tree->item,\
                    exec_tree->item + i, i , env);
            else if (exec_tree->item[i + 1] == '?')
                exec_tree->item = expand_status_code(exec_tree->item,\
                    exec_tree->item + i, i, status_code);
        }
    }
}

void expand_single_quote(t_btree *exec_tree)
{
    char *buffer;

    buffer = ft_strtrim(exec_tree->item, "\'");
    free(exec_tree->item);
    exec_tree->item = buffer;
}

void expand_double_quote(t_btree *exec_tree, int status_code, t_listt *env)
{
    char *buffer;

    buffer = ft_strtrim(exec_tree->item, "\"");
    free(exec_tree->item);
    exec_tree->item = buffer;
    expand_dollar_sign(exec_tree, status_code, env);
}
void expand_single_quote_heredoc(t_btree *exec_tree)
{
    char *buffer;

    buffer = ft_strtrim(exec_tree->item, "\'");
    free(exec_tree->item);
    exec_tree->item = buffer;
}

void expand_double_quote_heredoc(t_btree *exec_tree, t_listt *env)
{
    char *buffer;
    (void)env;
    buffer = ft_strtrim(exec_tree->item, "\"");
    free(exec_tree->item);
    exec_tree->item = buffer;
}
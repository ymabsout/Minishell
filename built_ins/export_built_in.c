/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:30:50 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/05 23:51:44 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static void export_no_args(t_listt *head_env)
{
    char **arr;

    while (head_env)
    {
        arr = ft_split((char *)(head_env->content), '=');
        if (!arr)
            exit(-1);
        if (!arr[1])
        {
            if (find_num_char(head_env->content, '='))
                printf("declare -x %s=\"\"\n", arr[0]);
            else
                printf("declare -x %s\n", arr[0]);
        }
        else
            printf("declare -x %s=\"%s\"\n", arr[0], arr[1]);
        free_double(arr);
        head_env = head_env->next;
    }
}

static void lol(t_listt *node, char *env_var)
{
    char **joined_var;
    char *final_form;

    joined_var = ft_split(env_var, '=');
    if (!joined_var)
        return (perror("malloc: "));
    final_form = ft_strjoin(node->content, joined_var[1]);
    if (!final_form)
        return (free_double(joined_var), perror("malloc: "));
    free_double(joined_var);
    // free(node->content);
    node->content = (void *)final_form;
}

static void replace_env(t_listt *node, char *env_var)
{
    char **arr;

    arr = ft_split(env_var, '=');
    if (!arr)
        return (perror("malloc: "));
    if (arr[0][ft_strlen(arr[0]) - 1] == '+')
        return (lol(node, env_var), free_double(arr));
    free_double(arr);
    // free(node->content);
    node->content = (void *)env_var;
}

static void add_env(t_listt **head_env, char *env_var)
{
    t_listt *node;
    char **arr;
    char *env_v;

    arr = ft_split(env_var, '+');
    if (!arr)
        return (perror("malloc: "));
    env_v = ft_strjoin(arr[0], arr[1]);
    if (!env_v)
        return (free_double(arr), perror("malloc: "));
    free_double(arr);
    node = ft_lstnew(env_v);
    if (!node)
        exit(-1);
    ft_lstadd_back(head_env, node);
}

static void export(t_listt **head_env, char *env_var)
{
    t_listt *curr;
    char **env_list;
    char **env_str;

    printf("[%s]\n", env_var);
    curr = *head_env;
    while (curr)
    {
        env_list = ft_split((char *)(curr->content), '=');
        if (!env_list)
            exit(-1);
        env_str = ft_split(env_var, '=');
        if (!env_str)
            (free_double(env_list), exit(-1));
        if (!ft_strncmp(env_list[0], env_str[0], ft_strlen(env_str[0])))
        {
            replace_env(curr, env_var);
            (free_double(env_list), free_double(env_str));
            return ;
        }
        (free_double(env_list), free_double(env_str));
        curr = curr->next;
    }
    add_env(head_env, env_var);
}

static int check_invalid_chars(char *cmd, int *is_plus)
{
    int i;
    char **arr;

    if (!cmd[0] || !ft_strncmp(cmd, "=", 2))
    {
        valid_id_error("export", cmd);
        return (1);
    }
    arr = ft_split(cmd, '=');
    if (!ft_isalpha(arr[0][0]) && arr[0][0] != '_')
    {
        valid_id_error("export", cmd);
        return (free_double(arr), 1);
    }
    i = 0;
    while (arr[0][++i])
    {
        if (arr[0][i + 1] == '\0' && arr[0][i] == '+')
        {
            *is_plus = 1;
            continue ;
        }
        if (!ft_isalnum(arr[0][i]) && arr[0][i] != '_')
            return (valid_id_error("export", cmd), free_double(arr), 1);
    }
    return (free_double(arr), 0);
}

//handle var+=something join if it s already their add if it s not!

static void export_plus(t_listt **head_env, char *env_var)
{
    t_listt *curr;
    char **env_list;
    char **env_str;

    curr = *head_env;
    while (curr)
    {
        env_list = ft_split((char *)(curr->content), '=');
        if (!env_list)
            exit(-1);
        env_str = ft_split(env_var, '=');
        if (!env_str)
            (free_double(env_list), exit(-1));
        if (!ft_strncmp(env_list[0], env_str[0], ft_strlen(env_str[0]) - 1))
        {
            replace_env(curr, env_var);
            (free_double(env_list), free_double(env_str));
            return ;
        }
        (free_double(env_list), free_double(env_str));
        curr = curr->next;
    }
    add_env(head_env, env_var);
}

int export_built_in(char **cmd, t_listt **head_env)
{
    int status_code;
    int i;
    int is_plus;

    status_code = 0;
    if (!cmd[1])
        return (export_no_args(*head_env), status_code);
    if (cmd[1][0] == '-')
    {
        ft_putstr_fd("export: no options required\n", 2);
        return (status_code = 1);
    }
    i = 0;
    is_plus = 0;
    while (cmd[++i])
    {
        if (check_invalid_chars(cmd[i], &is_plus))
        {
            status_code = 1;
            continue ;
        }
        if (is_plus)
        {
            export_plus(head_env, cmd[i]);
            is_plus = 0;
        }
        else
            export(head_env, cmd[i]);
    }
    return (status_code);
}

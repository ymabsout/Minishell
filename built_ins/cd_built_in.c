/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:27:03 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/03 19:18:33 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void insert_new_env(t_listt **head_env, char *key, char *val)
{
    t_listt *node;
    char *content;

    content = ft_strjoin(key, val);
    if (!content)
        exit(-1);
    node = ft_lstnew(content);
    if (!node)
        exit(-1);
    ft_lstadd_back(head_env, node);
}

void mutate_env_dirs(char *new_pwd, char *old_pwd, t_listt **head_env)
{
    t_listt *curr;
    int is_old_pwd;

    curr = *head_env;
    is_old_pwd = 0;
    while (curr)
    {
        if (!ft_strncmp(curr->content, "PWD", 3))
        {
            free((char *)(curr->content));
            curr->content = ft_strjoin("PWD=", new_pwd);
            if (!curr->content)
                return (perror("malloc: "));
        }
        if (!ft_strncmp(curr->content, "OLDPWD", 6))
        {
            (is_old_pwd = 1, free((char *)(curr->content)));
            curr->content = ft_strjoin("OLDPWD=", old_pwd);
            if (!curr->content)
                return (perror("malloc: "));
        }
        curr = curr->next;
    }
    if (!is_old_pwd)
        insert_new_env(head_env, "OLDPWD=", old_pwd);
}

// int handle_old_pwd(char **cmd, t_listt **head_env)
// {
//     t_listt *curr;
//     t_listt *old_pwd;
//     char **arr;
//     char *w_dir;

//     curr = *head_env;
//     old_pwd = NULL;
//     while (curr)
//     {
//         if (!ft_strncmp(curr->content, "OLDPWD", 6))
//         {
//             old_pwd = curr;
//             break ;
//         }
//         curr = curr->next;
//     }
//     if (!old_pwd)
//     {
//         ft_putstr_fd("cd: OLDPWD not set\n", 2);
//         return (1);
//     }
//     arr = ft_split(old_pwd->content, '=');
//     w_dir = getcwd(0, 0);
//     if (chdir(arr[1]) == -1)
//     {
//         perror("cd: ");
//         perror(arr[1]);
//         free_double(arr);
//         return (errno);
//     }
//     mutate_env_dirs(arr[1], w_dir, head_env);
//     free_double(arr);
//     free(w_dir);
//     return (0); 
// }

int cd_built_in(char **cmd, t_listt **head_env)
{
    char *w_dir;
    char *c_dir;

    // if (!ft_strncmp(cmd[1], "-", ft_strlen("-")))
    //     return (handle_old_pwd(cmd, head_env));
    w_dir = getcwd(0, 0);
    if (chdir(cmd[1]) == -1)
    {
        ft_putstr_fd("cd: ", 2);
        perror(cmd[1]);
        return (errno);
    }
    c_dir = getcwd(0, 0);
    printf("%s\n", c_dir);
    mutate_env_dirs(c_dir, w_dir, head_env);
    free(w_dir);
    free(c_dir);
    return (0);
}
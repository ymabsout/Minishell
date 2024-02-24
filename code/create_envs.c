/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:44:28 by smoumni           #+#    #+#             */
/*   Updated: 2024/02/24 17:29:59 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_listt *create_envs(char **env)
{
    t_listt *head_env;
    t_listt *node;
    int i;
    char *arr;

    i = -1;
    head_env = 0;
    while (env[++i])
    {
        arr = ft_strdup(env[i]);
        if (!arr)
            exit(-1);
        node = ft_lstnew(arr);
        if (!node)
            exit(-1);
        ft_lstadd_back(&head_env, node);
    }
    return (head_env);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:44:28 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/13 17:49:16 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static t_listt	*create_envs_default(void)
{
	t_listt	*head_env;
	t_listt	*node;
	char	*curr_dir;
	char	*str;

	head_env = 0;
	curr_dir = getcwd(0, 0);
	str = ft_strjoin("PWD=", curr_dir);
	free(curr_dir);
	node = ft_lstnew(str);
	ft_lstadd_back(&head_env, node);
	str = ft_strdup("SHLVL=1");
	node = ft_lstnew(str);
	ft_lstadd_back(&head_env, node);
	str = ft_strjoin("PATH=", PATH);
	node = ft_lstnew(str);
	ft_lstadd_back(&head_env, node);
	return (head_env);
}

t_listt	*create_envs(char **env)
{
	t_listt	*head_env;
	t_listt	*node;
	int		i;
	char	*arr;

	i = -1;
	head_env = 0;
	if (!env[0])
		return (create_envs_default());
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

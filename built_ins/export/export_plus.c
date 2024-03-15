/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_plus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:03:22 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/12 16:04:00 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

void	export_plus(t_listt **head_env, char *env_var)
{
	t_listt	*curr;
	char	**env_list;
	char	**env_str;

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

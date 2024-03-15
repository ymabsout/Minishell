/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:18:09 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 00:13:48 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	env_built_in(char **cmd, t_listt *head_env)
{
	if (cmd[1] != NULL)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": illegal option\n", 2);
		ft_putstr_fd("usage: env\n", 2);
		return (1);
	}
	while (head_env)
	{
		if (find_num_char(head_env->content, '='))
			printf("%s\n", (char *)(head_env->content));
		head_env = head_env->next;
	}
	return (0);
}

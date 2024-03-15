/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:10:24 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 03:38:44 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	check_invalid_chars(char *cmd)
{
	int	i;

	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
	{
		valid_id_error("unset", cmd);
		return (1);
	}
	i = 0;
	while (cmd[++i])
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
		{
			valid_id_error("unset", cmd);
			return (1);
		}
	}
	return (0);
}

static void	del(void *con)
{
	free((char *)con);
}

static void	unset_env(char *cmd, t_listt **head_env)
{
	t_listt	*curr;
	t_listt	*prev;

	curr = (*head_env);
	if (!ft_strncmp((char *)(curr->content), cmd, ft_strlen(cmd)))
	{
		(*head_env) = curr->next;
		curr->next = NULL;
		ft_lstdelone(curr, del);
		return ;
	}
	curr = curr->next;
	prev = *head_env;
	while (curr)
	{
		if (!ft_strncmp((char *)(curr->content), cmd, ft_strlen(cmd)))
		{
			prev->next = curr->next;
			curr->next = NULL;
			ft_lstdelone(curr, del);
			return ;
		}
		curr = curr->next;
		prev = prev->next;
	}
}

int	unset_built_in(char **cmd, t_listt **head_env)
{
	int	i;
	int	status_code;

	status_code = 0;
	if (cmd[1] == NULL)
		return (status_code = 1);
	if (cmd[1][0] == '-')
	{
		ft_putstr_fd("unset: no options required\n", 2);
		return (status_code = 1);
	}
	i = -1;
	while (cmd[++i])
	{
		if (check_invalid_chars(cmd[i]))
		{
			status_code = 1;
			continue ;
		}
		unset_env(cmd[i], head_env);
	}
	return (status_code);
}

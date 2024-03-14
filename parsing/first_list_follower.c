/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_list_follower.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 21:31:20 by ymabsout          #+#    #+#             */
/*   Updated: 2024/03/14 21:49:48 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	*white_space_handle(char *cmd, int *index, t_list **root)
{
	char	*tmp;

	if ((*index) != 0)
	{
		tmp = ft_substr(cmd, 0, (*index));
		lst_addback(root, set_correct_type(lst_new(ft_strdup(tmp)), 1));
		free(tmp);
	}
	lst_addback(root, set_correct_type(lst_new(ft_strdup(" ")), 1));
	while (cmd[++(*index)] && (cmd[(*index)] == ' ' || cmd[(*index)] == '\t'))
		;
	tmp = ft_strdup (cmd + (*index));
	free(cmd);
	cmd = ft_strdup(tmp);
	free(tmp);
	return (cmd);
}

void	*statement_delim(char *cmd, int *index, int *track, t_list **root)
{
	char	*tmp;

	if ((cmd[(*index)] == '|' && cmd[(*index) + 1] != cmd[(*index)]) \
		|| cmd[(*index)] != cmd[(*index) + 1])
	{
		tmp = ft_substr(cmd, (*index), 1);
		lst_addback(root, set_correct_type(lst_new(ft_strdup(tmp)), 1));
		(*track) = 0;
	}
	else
	{
		tmp = ft_substr(cmd, (*index), 2);
		lst_addback(root, set_correct_type(lst_new(ft_strdup(tmp)), 2));
		(*track) = 1;
	}
	free(tmp);
	return (cmd);
}

void	*delim_follows(char *cmd, t_list **root, int *index, int *track)
{
	char	*tmp;

	if (cmd[(*index)] == '&')
	{
		if (cmd[(*index)] == cmd[(*index) + 1])
			lst_addback(root, set_correct_type(lst_new(ft_strdup("&&")), 2));
		else
			return (printf("syntax error %c\n", \
				cmd[(*index)]), lst_clear(root), NULL);
		(*track) = 1;
	}
	else if (delimeter(cmd[(*index) + 1]) && cmd[(*index) + 1] != ')'\
		&& cmd[(*index) + 1] != '(')
		statement_delim(cmd, index, track, root);
	else
	{
		tmp = ft_substr(cmd, (*index), 1);
		lst_addback(root, set_correct_type(lst_new(ft_strdup(tmp)), 1));
		free(tmp);
	}
	return (cmd);
}

void	*handle_delimeter(char *cmd, t_list **root, int *index, int *track)
{
	char	*tmp;

	if ((*index) != 0)
	{
		tmp = ft_substr(cmd, 0, (*index));
		lst_addback(root, set_correct_type(lst_new(ft_strdup(tmp)), 1));
		free(tmp);
	}
	if (cmd[(*index)] != '\0')
	{
		cmd = delim_follows(cmd, root, index, track);
		if (!cmd)
			return (NULL);
	}
	if ((*index) != ft_strlen(cmd))
	{
		tmp = ft_strdup(cmd + (*index) + 1 + (*track));
		free(cmd);
		cmd = ft_strdup(tmp);
		(*track) = 0;
		(*index) = -1;
		free(tmp);
	}
	return (cmd);
}

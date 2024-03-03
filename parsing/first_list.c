/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:30:32 by ymabsout          #+#    #+#             */
/*   Updated: 2024/03/03 20:18:40 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void  *white_space_handle(char *cmd, int *index, t_list **root)
{
	char *tmp;

	if ((*index) != 0)
	{
		tmp = ft_substr(cmd, 0, (*index));
		lst_addback(root, set_correct_type(lst_new(ft_strdup(tmp)), 1));
		free(tmp);
	}
	lst_addback(root, set_correct_type(lst_new(ft_strdup(" ")), 1));
	while (cmd[++(*index)] && cmd[(*index)] == ' ')
		;
	tmp = ft_strdup (cmd + (*index));
	free(cmd);
	cmd = ft_strdup(tmp);
	free(tmp);
	return(cmd);
}

void *statement_delim(char *cmd, int *index, int *track, t_list **root)
{
	char *tmp;

	if ((cmd[(*index)] == '|' && cmd[(*index) + 1] != cmd[(*index)]) || cmd[(*index)] != cmd[(*index) + 1])
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

void *delim_follows(char *cmd, t_list **root, int *index, int *track)
{
	char *tmp;

	if (cmd[(*index)] == '&')
	{
		if (cmd[(*index)] == cmd[(*index) + 1])
			lst_addback(root, set_correct_type(lst_new(ft_strdup("&&")), 2));
		else
			return (printf("syntax error near %c\n", cmd[(*index)]), lst_clear(root), NULL);
		(*track) = 1;
	}
	else if (delimeter(cmd[(*index) + 1]) && cmd[(*index) + 1] != ')' && cmd[(*index) + 1] != '(')
		statement_delim(cmd, index, track, root);
	else
	{
		tmp = ft_substr(cmd, (*index), 1);
		lst_addback(root, set_correct_type(lst_new(ft_strdup(tmp)), 1));
		free(tmp);
	}
	return (cmd);
}

void *handle_delimeter(char *cmd, t_list **root, int *index,  int *track)
{
	char *tmp;

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

void *dbl_sgl_handle(t_list **root, char *cmd, int *index)
{
	char *tmp;

	if ((*index) != 0)
	{
		tmp = ft_substr(cmd, 0, (*index));
		lst_addback(root, set_correct_type(lst_new(ft_strdup(tmp)), 1));
		free(tmp);
		tmp = ft_substr(cmd ,(*index), ft_strlen(cmd + (*index)));
		free(cmd);
		cmd = ft_strdup(tmp);
		free(tmp);
	}
	cmd = get_quotes(root, cmd, (*index));
	if (!cmd)
		return (NULL);
	(*index) = -1;
	return (cmd);
}

void *tokenize_lex(char *cmd)
{
	t_list *root;
	int index;
	int track;

	track = 0;
	root = NULL;
	index = -1;
	while (++index <= ft_strlen(cmd))
	{
		if (cmd[index] == ' ' || cmd[index] == '\t')
		{
			cmd = white_space_handle(cmd, &index, &root);
			index = -1;
		}
		else if (delimeter(cmd[index]))
			cmd = handle_delimeter(cmd, &root, &index, &track);
		else if (db_sl_quote(cmd[index]))
		{
			cmd = dbl_sgl_handle(&root, cmd ,&index);
			if (!cmd)
				return (lst_clear(&root), NULL);
		}
	}
	free(cmd);
	return(root);
}

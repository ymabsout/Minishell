/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:30:32 by ymabsout          #+#    #+#             */
/*   Updated: 2024/03/15 07:25:30 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	*dbl_sgl_handle(t_list **root, char *cmd, int *index)
{
	char	*tmp;

	if ((*index) != 0)
	{
		tmp = ft_substr(cmd, 0, (*index));
		lst_addback(root, set_correct_type(lst_new(ft_strdup(tmp)), 1));
		free(tmp);
		tmp = ft_substr(cmd, (*index), ft_strlen(cmd + (*index)));
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

void	*tokenize_lex(char *cmd)
{
	t_list	*root;
	int		index;
	int		track;

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
			cmd = dbl_sgl_handle(&root, cmd, &index);
			if (!cmd)
				return (lst_clear(&root), NULL);
		}
	}
	free(cmd);
	return (root);
}

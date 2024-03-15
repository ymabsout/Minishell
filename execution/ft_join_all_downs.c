/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_all_downs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 03:49:31 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 07:27:53 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*ft_joinalldowns(t_btree **exec_tree, int status_code, t_listt *env)
{
	char	*str;
	char	*old_str;
	t_btree	*down;

	if ((*exec_tree)->type & token_single_q)
		expand_single_quote((*exec_tree));
	else
		expand_double_quote(exec_tree, status_code, env);
	str = (*exec_tree)->item;
	down = (*exec_tree)->down;
	while (down)
	{
		old_str = str;
		if (down->type & token_single_q)
			expand_single_quote(down);
		else
			expand_double_quote(&down, status_code, env);
		str = ft_strjoin(old_str, down->item);
		if (!str)
			return (free(old_str), NULL);
		free(old_str);
		down = down->down;
	}
	return (str);
}

char	*ft_joinalldowns_heredoc(t_btree *exec_tree)
{
	char	*str;
	char	*old_str;
	t_btree	*down;

	if (exec_tree->type & token_single_q)
		expand_single_quote_heredoc(exec_tree);
	else
		expand_double_quote_heredoc(exec_tree);
	str = exec_tree->item;
	exec_tree = exec_tree->down;
	while (exec_tree)
	{
		old_str = str;
		if (exec_tree->type & token_single_q)
			expand_single_quote_heredoc(exec_tree);
		else
			expand_double_quote_heredoc(exec_tree);
		str = ft_strjoin(old_str, exec_tree->item);
		if (!str)
			return (free(old_str), NULL);
		down = exec_tree->down;
		(free(old_str), free(exec_tree->item), free(exec_tree));
		exec_tree = down;
	}
	return (str);
}

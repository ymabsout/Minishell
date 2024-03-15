/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:20:40 by ymabsout          #+#    #+#             */
/*   Updated: 2024/03/15 07:28:16 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

t_btree	*parse_ampersand_or(t_list **root)
{
	t_btree	*tmp;
	t_btree	*tmp1;
	t_btree	*token;
	t_btree	*tmp2;

	tmp = parse_pipe(root);
	while ((*root) && (*root)->type & token_and_or)
	{
		token = duplicate_for_tree(*root);
		(*root) = (*root)->next;
		tmp1 = parse_pipe(root);
		tmp2 = tmp;
		if (!tmp1)
			return (tree_freeir(token, tmp, tmp1), NULL);
		token->left = tmp2;
		token->right = tmp1;
		tmp = token;
	}
	return (tmp);
}

t_btree	*parse_pipe(t_list **root)
{
	t_btree	*tmp;
	t_btree	*tmp1;
	t_btree	*token;
	t_btree	*tmp2;

	tmp = parse_heredoc_append(root);
	while (*root && (*root)->type & token_pipe)
	{
		token = duplicate_for_tree(*root);
		(*root) = (*root)->next;
		tmp1 = parse_heredoc_append(root);
		tmp2 = tmp;
		if (!tmp1 \
			|| (!(tmp1->type & (token_parse | token_and_or)) \
			&& !tmp1->flag_subshell))
			return (tree_freeir(token, tmp, tmp1), NULL);
		token->left = tmp2;
		token->right = tmp1;
		tmp = token;
	}
	return (tmp);
}

t_btree	*parse_heredoc_append(t_list **root)
{
	t_btree	*tmp;
	t_btree	*tmp1;
	t_btree	*token;
	t_btree	*tmp2;

	tmp = NULL;
	if ((*root) && !((*root)->type & token_red_here_doc))
		tmp = parse_cmd(root);
	while (*root && (*root)->type & token_red)
	{
		token = duplicate_for_tree(*root);
		(*root) = (*root)->next;
		tmp1 = parse_cmd(root);
		tmp2 = tmp;
		if (!tmp1 \
			|| (tmp && !(tmp1->type & (token_word | token_quote))))
			return (tree_freeir(token, tmp, tmp1), NULL);
		token->left = tmp2;
		token->right = tmp1;
		tmp = token;
	}
	return (tmp);
}

t_btree	*parse_cmd(t_list **root)
{
	t_btree	*tmp;
	t_btree	*tmp2;

	tmp = NULL;
	while ((*root) && (*root)->type & (token_word | token_quote))
	{
		tmp = lstaddback_tree(tmp, duplicate_for_tree(*root));
		if ((*root)->down)
			add_down_tree((*root)->down, &tmp);
		(*root) = (*root)->next;
		while ((*root) && (*root)->type & (token_word | token_quote))
		{
			tmp = lstaddback_tree(tmp, duplicate_for_tree(*root));
			if ((*root)->down)
			{
				tmp2 = lst_last_tree(tmp);
				add_down_tree((*root)->down, &tmp2);
			}
			(*root) = (*root)->next;
		}
		return (tmp);
	}
	if ((*root) && (*root)->type & token_par_in)
		tmp = parin(root);
	return (tmp);
}

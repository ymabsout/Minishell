/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:33:43 by ymabsout          #+#    #+#             */
/*   Updated: 2024/03/14 19:44:26 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

t_btree	*parin(t_list **root)
{
	t_btree	*tmp;

	(*root) = (*root)->next;
	tmp = parse_ampersand_or(root);
	if (!*root || !((*root)->type & token_par_out) || !tmp)
		return (free_tree(tmp), NULL);
	(*root) = (*root)->next;
	tmp->flag_subshell = 1;
	return (tmp);
}

void	tree_freeir(t_btree *token, t_btree *tmp, t_btree *tmp1)
{
	free_tree(token);
	free_tree(tmp1);
	free_tree(tmp);
}

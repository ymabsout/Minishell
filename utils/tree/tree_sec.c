/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_sec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 07:14:02 by ymabsout          #+#    #+#             */
/*   Updated: 2024/03/15 07:28:21 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

t_btree	*lstaddback_tree(t_btree *root, t_btree *leaf)
{
	t_btree	*holder;

	if (!root)
	{
		root = leaf;
		return (root);
	}
	holder = root;
	while (root && root->next)
		root = root->next;
	root->next = leaf;
	root = holder;
	return (root);
}

void	lstadd_down_tree(t_btree **root, t_btree *leaf)
{
	t_btree	*holder;

	holder = (*root);
	while (holder && holder->down)
		holder = holder->down;
	holder->down = leaf;
	holder = (*root);
}

void	add_down_tree(t_list *root, t_btree **leaf)
{
	t_btree	*hold;

	hold = (*leaf);
	while (root)
	{
		lstadd_down_tree(leaf, duplicate_for_tree(root));
		root = root->down;
	}
	*leaf = hold;
}

t_btree	*duplicate_for_tree(t_list *root)
{
	t_btree	*node;

	node = malloc(sizeof(t_btree));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_btree));
	node->item = ft_strdup((char *)root->content);
	node->type = root->type;
	return (node);
}

t_btree	*lst_last_tree(t_btree *root)
{
	while (root && root->next)
		root = root->next;
	return (root);
}

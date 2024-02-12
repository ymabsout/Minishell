/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:20:40 by ymabsout          #+#    #+#             */
/*   Updated: 2024/02/12 15:36:45 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../m1.h"

t_btree *btree_create_node(void *item)
{
    t_btree *node_tree;

    node_tree = malloc(sizeof(t_btree));
    if (!node_tree)
        return (NULL);
    node_tree->item = item;
    node_tree->left = NULL;
    node_tree->right = NULL;
    return (node_tree);
}

void btree_insert_data(t_btree **root, void *item)
{
    if (!(*root))
    {
        *root = btree_create_node(item);
        return ;
    }
   if (!ft_strncmp((char *)item, "<", 1) || !ft_strncmp((char *)item, ">", 1) \
			 || !ft_strncmp(item, "|", 1))
        btree_insert_data(&(*root)->right, item);
    else if (!(*root)->left)
        btree_insert_data(&(*root)->left, item);
    else
        btree_insert_data(&(*root)->right, item);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:20:40 by ymabsout          #+#    #+#             */
/*   Updated: 2024/02/16 17:44:27 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../m1.h"

// t_btree *btree_create_node(t_list *item)
// {
//     t_btree *node_tree;

//     node_tree = malloc(sizeof(t_btree));
//     if (!node_tree)
//         return (NULL);
//     node_tree->item = item;
//     node_tree->left = NULL;
//     node_tree->right = NULL;
//     return (node_tree);
// }

void print_tree(t_btree *root) {
    if (!root)
        return ;
    printf("NODE: %s\n", (char *)root->item);
    print_tree(root->left);
    printf("^^^%s^^^\n", (char *)root->item);
    print_tree(root->right);
}


t_btree *duplicate_for_tree(t_list *root)
{
    t_btree *node;

    node = malloc(sizeof(t_btree));
    if (!node)
        return (NULL);
    node->item = ft_strdup(root->content);
    node->type = root->typeofcontent;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

t_btree *parse_cmd(t_list **root)
{
    t_btree *tmp;

    if ((*root)->typeofcontent & token_word)
    {
        tmp = duplicate_for_tree(*root);
        (*root)= (*root)->next;
        return (tmp); // return the command node;
    }
    else
    {
        printf("expected word , got %s\n", (*root)->content);
        exit(EXIT_FAILURE);
    }
}
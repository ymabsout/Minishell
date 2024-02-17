/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:20:40 by ymabsout          #+#    #+#             */
/*   Updated: 2024/02/17 15:13:01 by ymabsout         ###   ########.fr       */
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

void print_next_tree(t_btree *root){
    while (root)
    {
        printf("Next is ->:%s\n", root->item);
        root = root->next;
    }
}

void print_down_tree(t_btree *root){
    while (root)
    {
        printf("down is ->:%s\n", root->item);
        root = root->down;
    }
}

void print_tree(t_btree *root) {
    if (!root)
        return ;
    printf("NODE: %s\n", (char *)root->item);
    if (root->down)
        print_down_tree(root->down);
    if (root->next)
        print_next_tree(root->next);
    print_tree(root->left);
    printf("^^^%s^^^\n", (char *)root->item);
    print_tree(root->right);
}

// void	tree_add_down(t_btree **lst, t_btree *new)
// {
// 	t_btree	*head;

// 	head = *lst;
// 	if (!*lst)
// 	{
// 		head->down = new;
// 		new->up = *lst;
// 		return ;
// 	}
// 	while (head->down)
// 		head = head->down;
// 	head->down = new;
// }

void lstaddback_tree(t_btree **root, t_btree *leaf)
{
    while ((*root) && (*root)->next)
        (*root) = (*root)->next;
    (*root)->next = leaf;
}

void lstadd_down_tree(t_btree **root, t_btree *leaf)
{
    while ((*root) && (*root)->down)
        (*root) = (*root)->down;
    (*root)->down = leaf;
}

t_btree *duplicate_for_tree(t_list *root)
{
    t_btree *node;

    node = malloc(sizeof(t_btree));
    if (!node)
        return (NULL);
    ft_memset(node , 0, sizeof(t_btree));
    node->item = ft_strdup(root->content);
    node->type = root->typeofcontent;
    return (node);
}

t_btree *parse_ampersand_or(t_list **root)
{
    t_btree *tmp;
    t_btree *tmp1;
    t_btree *token;
    t_btree *tmp2;
    
    tmp = parse_pipe(root);
    while ((*root) && (*root)->typeofcontent & token_and_or)
    {
        token = duplicate_for_tree(*root);
        (*root) = (*root)->next;
        tmp1 = parse_pipe(root);
        tmp2 = tmp;
        token->left = tmp2;
        token->right = tmp1;
        tmp = token;
    }
    return (tmp);
}


t_btree *parse_pipe(t_list **root)
{
    t_btree *tmp;
    t_btree *tmp1;
    t_btree *token;
    t_btree *tmp2;

    tmp = parse_heredoc_append(root);
    while (*root && (*root)->typeofcontent & token_pipe)
    {
        token = duplicate_for_tree(*root);
        (*root) = (*root)->next;
        tmp1 = parse_heredoc_append(root);
        tmp2 = tmp;
        if (!(tmp1->type & (token_word | token_quote | token_red | token_pth)))
        {
            printf("Syntax error\n");
            return (NULL);
        }
        token->left = tmp2;
        token->right = tmp1;
        tmp = token;
    }
    return(tmp);
}

t_btree *parse_heredoc_append(t_list **root)
{
    t_btree *tmp;
    t_btree *tmp1;
    t_btree *token;
    t_btree *tmp2;
    
    tmp = NULL;
    if (!((*root)->typeofcontent & token_red_here_doc))
        tmp = parse_cmd(root);
    while (*root && (*root)->typeofcontent & (token_heredoc_append))
    {
        token = duplicate_for_tree(*root);
        (*root) = (*root)->next;
        tmp1 = parse_cmd(root);
        tmp2 = tmp;
        if (!(tmp1->type & (token_word | token_quote)))
        {
            printf("Syntax Error\n");
            return (NULL);
        }
        token->left = tmp2;
        token->right = tmp1;
        tmp = token;
    }
    return (tmp);
}

void add_down_tree(t_list *root, t_btree **leaf)
{
    while (root)
    {
        lstadd_down_tree(leaf, duplicate_for_tree(root));
        root = root->down;
    }
}

t_btree *parse_cmd(t_list **root)
{
    t_btree *tmp;

    if ((*root)->typeofcontent & (token_word | token_quote))
    {
        tmp = duplicate_for_tree(*root);
        if ((*root)->down)
            add_down_tree((*root)->down, &tmp);
        (*root)= (*root)->next;
        while ((*root) && (*root)->typeofcontent & (token_word | token_quote))
        {
            lstaddback_tree(&tmp, duplicate_for_tree(*root));
            if ((*root)->down)
                add_down_tree((*root)->down, &tmp);
            (*root) = (*root)->next;
        }
        return (tmp); // return the command node;
    }
    if ((*root)->typeofcontent & token_par_in)
    {
        (*root) = (*root)->next;
        tmp = parse_ampersand_or(root);
        if (!*root || !((*root)->typeofcontent & token_par_out))
        {
            printf("Syntax error\n");
            exit (EXIT_FAILURE);
        }
        (*root) = (*root)->next;
        return (tmp);
    }
    else
    {
        printf("expected word , got %s\n", (*root)->content);
        exit(EXIT_FAILURE);
    }
}

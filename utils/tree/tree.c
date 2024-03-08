/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:20:40 by ymabsout          #+#    #+#             */
/*   Updated: 2024/03/02 23:48:44 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

void print_next_tree(t_btree *root){
    while (root)
    {
        if (root->down)
            print_down_tree(root->down);
        printf("Next is ->:%s\n", root->item);
        if (root->down)
            print_down_tree(root);
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

t_btree *lstaddback_tree(t_btree *root, t_btree *leaf)
{
    t_btree *holder;

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

void lstadd_down_tree(t_btree **root, t_btree *leaf)
{
    t_btree *holder;
    
    holder = (*root);
    while (holder && holder->down)
        holder = holder->down;
    holder->down = leaf;
    holder = (*root);
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


void add_down_tree(t_list *root, t_btree **leaf)
{
    t_btree * hold;
    hold = (*leaf);
    printf("%s\n", hold->item);
    while (root)
    {
        lstadd_down_tree(leaf, duplicate_for_tree(root));
        root = root->down;
    }
    *leaf = hold;
}

t_btree *duplicate_for_tree(t_list *root)
{
    t_btree *node;

    node = malloc(sizeof(t_btree));
    if (!node)
        return (NULL);
    ft_memset(node , 0, sizeof(t_btree));
    node->item = ft_strdup((char *)root->content);
    node->typeofcontent = root->typeofcontent;
    // free(root->content);
    // free(root);
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
        if (!tmp1)
            return (NULL);
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
        if (!tmp1 \
            || !(tmp1->typeofcontent & (token_parse | token_and_or)))
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
    if ((*root) && !((*root)->typeofcontent & token_red_here_doc))
        tmp = parse_cmd(root);
    while (*root && (*root)->typeofcontent & token_red)
    {
        token = duplicate_for_tree(*root);
        (*root) = (*root)->next;
        tmp1 = parse_cmd(root);
        tmp2 = tmp;
        if (!tmp1 || (tmp && !(tmp1->typeofcontent & (token_word | token_quote))))
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

t_btree *parse_cmd(t_list **root)
{
    t_btree *tmp;
    t_btree *tmp2;

    tmp = NULL;
    while ((*root) && (*root)->typeofcontent & (token_word | token_quote))
    {
        tmp = lstaddback_tree(tmp, duplicate_for_tree(*root));
        if ((*root)->down)
            add_down_tree((*root)->down, &tmp);
        (*root) = (*root)->next;
        while ((*root) && (*root)->typeofcontent & (token_word | token_quote))
        {
            tmp = lstaddback_tree(tmp, duplicate_for_tree(*root));
            if ((*root)->down)
            {
                tmp2 = lst_last_tree(tmp);
                add_down_tree((*root)->down, &tmp2);
            }
            (*root) = (*root)->next;
        }
        return (tmp); // return the command node;
    }
    if ((*root) && (*root)->typeofcontent & token_par_in)
    {
        (*root) = (*root)->next;
        tmp = parse_ampersand_or(root);
        if (!*root || !((*root)->typeofcontent & token_par_out) || !tmp)
        {
            printf("Syntax error\n");
            return (NULL);
        }
        (*root) = (*root)->next;
        tmp->flag_subshell = 1;
    }
    return (tmp); // return the command node; or NULL if nothing matches!
}

t_btree *lst_last_tree(t_btree *root)
{
    while (root && root->next)
        root = root->next;
    return (root);
}

// command to check ((ls) | (ls -la))
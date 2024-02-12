/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:43:08 by ymabsout          #+#    #+#             */
/*   Updated: 2024/02/12 15:36:43 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../m1.h"

t_list *lst_new(char *content)
{
	t_list *node;

	node = malloc(sizeof (t_list));
	if (!node)
		return (NULL);
	node->content = ft_strdup((char *)content);
	// free(content);
	node->next = NULL;
	return (node);
}

void	lst_addback(t_list **lst, t_list *new)
{
	t_list	*head;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		new->next = NULL;
		return ;
	}
	head = (*lst);
	while (head->next != NULL)
		head = head->next;
	head->next = new;
}

t_list *duplicate_node(t_list *root)
{
	t_list *new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = ft_strdup(root->content);
	new->typeofcontent = root->typeofcontent;
	new->next = NULL;
	return (new);
}

void deletenode(t_list *holder, t_list *node_delete)
{
	t_list *next_curr;

	if (node_delete->next)
		next_curr = node_delete->next;
	(free(node_delete), node_delete = NULL);
	holder->next = next_curr;
}

t_list *lst_last(t_list *root)
{
	while(root->next)
		root = root->next;
	return (root);
}
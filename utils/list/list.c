/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:43:08 by ymabsout          #+#    #+#             */
/*   Updated: 2024/02/24 17:38:14 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

t_list *lst_new(char *content)
{
	t_list *node;

	node = malloc(sizeof (t_list));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_list));
	node->content = (char *)ft_strdup((char *)content);
	free(content);
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
	new->previous = head;
	new->next = NULL;
}
void	lst_add_down(t_list **lst, t_list *new)
{
	t_list	*head;

	if (!lst || !new)
		return ;
	head = *lst;
	if (!*lst)
	{
		head->down = new;
		new->up = *lst;
		return ;
	}
	while (head->next)
		head = head->next;
	while (head->down)
		head = head->down;
	head->down = new;
	new->up = head;
}

t_list *duplicate_node(t_list *root)
{
	t_list *new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content =  ft_strdup((char *)root->content);
	new->typeofcontent = root->typeofcontent;
	new->down = root->down;
	new->next = root->next;
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
	if (!root)
		return (root);
	while(root->next)
		root = root->next;
	return (root);
}

t_list *lst_last_down(t_list *root)
{
	while (root->down)
		root = root->down;
	return (root);
}
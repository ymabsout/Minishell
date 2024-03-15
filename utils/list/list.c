/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:43:08 by ymabsout          #+#    #+#             */
/*   Updated: 2024/03/15 00:50:07 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

t_list	*lst_new(char *content)
{
	t_list	*node;

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
	new->down = NULL;
}

t_list	*duplicate_node(t_list *root)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = ft_strdup((char *)root->content);
	new->type = root->type;
	new->down = root->down;
	return (new);
}

void	clear_down(t_list **root)
{
	t_list	*hold;

	while ((*root))
	{
		hold = (*root)->down;
		free((*root)->content);
		free((*root));
		(*root) = hold;
	}
	(*root) = NULL;
}

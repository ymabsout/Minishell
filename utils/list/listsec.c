/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listsec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 07:18:39 by ymabsout          #+#    #+#             */
/*   Updated: 2024/03/15 07:18:40 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

void	lst_clear(t_list **root)
{
	t_list	*holder;
	t_list	*tmp;

	(void)tmp;
	while (*root)
	{
		holder = (*root)->next;
		free((*root)->content);
		if ((*root)->down)
		{
			tmp = (*root)->down;
			clear_down(&(*root)->down);
		}
		free((*root));
		(*root) = holder;
	}
	(*root) = NULL;
}

t_list	*lst_last(t_list *root)
{
	if (!root)
		return (root);
	while (root->next)
		root = root->next;
	return (root);
}

t_list	*lst_last_down(t_list *root)
{
	while (root->down)
		root = root->down;
	return (root);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:43:08 by ymabsout          #+#    #+#             */
/*   Updated: 2024/02/01 10:20:46 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m1.h"

t_list *lst_new(void *content)
{
	t_list *node;

	node = malloc(sizeof (t_list);
	if (!node)
		return (NULL);
	node->content = ft_strdup((char *)content);
	node->next = NULL;
	return (node);
}

void lst_addfront(t_list **root, t_list *node)
{
	t_list *hold;

	if (!(*root))
	{
		(*root)->next = node;
		return ;
	}
	hold = *root;
	while (hold->next != NULL)
		hold = hold->next;
	hold->next = node; 
}

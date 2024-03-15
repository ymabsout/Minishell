/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:13:45 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/06 20:48:24 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_lstclear(t_listt **lst, void (*del)(void *))
{
	t_listt	*list;
	t_listt	*tmp;

	if (!del || !lst || *lst == NULL)
		return ;
	list = *lst;
	while (list)
	{
		tmp = list->next;
		del(list->content);
		free(list);
		list = tmp;
	}
	*lst = NULL;
}

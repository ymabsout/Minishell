/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 23:13:31 by smoumni           #+#    #+#             */
/*   Updated: 2024/02/24 17:27:45 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_listt	*ft_lstmap(t_listt *lst, void *(*f)(void *), void (*del)(void *))
{
	t_listt	*new;
	t_listt	*head;
	void	*data;

	if (!lst || !f || !del)
		return (NULL);
	head = NULL;
	while (lst)
	{
		data = f(lst->content);
		new = ft_lstnew(data);
		if (!new)
		{
			del(data);
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, new);
		lst = lst->next;
	}
	return (head);
}

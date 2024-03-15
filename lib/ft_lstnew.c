/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:06:57 by smoumni           #+#    #+#             */
/*   Updated: 2024/02/24 17:27:02 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_listt	*ft_lstnew(void *content)
{
	t_listt	*new_list;

	new_list = (t_listt *)malloc(sizeof(t_listt));
	if (!new_list)
		return (NULL);
	new_list->content = content;
	new_list->next = NULL; 
	return (new_list);
}

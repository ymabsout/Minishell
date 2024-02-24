/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:24:51 by smoumni           #+#    #+#             */
/*   Updated: 2024/02/24 17:27:58 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_lstdelone(t_listt *lst, void (*del)(void *))
{
	if (!del || !lst)
		return ;
	del(lst->content);
	free(lst);
}

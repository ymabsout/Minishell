/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_dollar_sign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 06:44:24 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 07:02:19 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static t_btree	*lstnew(char *content)
{
	t_btree	*new_list;

	new_list = (t_btree *)malloc(sizeof(t_btree));
	if (!new_list)
		return (NULL);
	ft_memset(new_list, 0, sizeof(t_btree));
	new_list->item = content;
	return (new_list);
}

static t_btree	*setting_node(t_btree **curr, char *str)
{
	t_btree	*next;
	t_btree	*node;

	next = (*curr)->next;
	node = lstnew(ft_strdup(str));
	node->next = next;
	(*curr)->next = node;
	(*curr) = (*curr)->next;
	return (node);
}

void	split_dollar_sign(t_btree **exec_tree)
{
	t_btree	*node;
	t_btree	*curr;
	char	**arr;
	int		i;

	i = -1;
	curr = (*exec_tree);
	arr = ft_split((*exec_tree)->item, ' ');
	while (arr[++i])
	{
		if (!i)
		{
			free(curr->item);
			curr->item = ft_strdup(arr[i]);
		}
		else
			node = setting_node(&curr, arr[i]);
	}
	free_double(arr);
	if (i > 1)
	{
		node->down = (*exec_tree)->down;
		(*exec_tree)->down = 0;
		(*exec_tree) = node;
	}
}

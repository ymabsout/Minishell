/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wild_card.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:47:34 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 04:00:13 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

static void	add_back(t_btree **lst, t_btree *new)
{
	t_btree	*curr;

	if (!new || !lst)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

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

static t_btree	*closing_dir(t_btree *whole, DIR *dir)
{
	closedir(dir);
	if (!whole)
		return (0);
	return (whole);
}

static DIR	*init_dir(t_btree **whole, struct dirent **dp)
{
	char	*wd;
	DIR		*dir;

	wd = getcwd(0, 0);
	dir = opendir(wd);
	free(wd);
	if (!dir)
		return (0);
	*whole = 0;
	*dp = readdir(dir);
	return (dir);
}

t_btree	*check_wild_card(char *str)
{
	DIR				*dir;
	struct dirent	*dp;
	char			*matched;
	t_btree			*whole;

	dir = init_dir(&whole, &dp);
	if (!dir)
		return (0);
	while (dp)
	{
		if (dp->d_name[0] == '.')
		{
			dp = readdir(dir);
			continue ;
		}
		matched = match(dp->d_name, str);
		if (!matched)
		{
			dp = readdir(dir);
			continue ;
		}
		add_back(&whole, lstnew(ft_strdup(matched)));
		dp = readdir(dir);
	}
	return (closing_dir(whole, dir));
}

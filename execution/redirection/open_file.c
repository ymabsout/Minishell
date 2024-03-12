/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:51:28 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/12 18:11:34 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

static int	open_in_file(t_btree *exec_tree)
{
	int	fd;

	if (access(exec_tree->string[0], F_OK) == -1)
		return (-1);
	if (access(exec_tree->string[0], R_OK) == -1)
		return (-3);
	fd = open(exec_tree->string[0], O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	open_file(t_btree *exec_tree, int flag, int status_code, t_listt *env)
{
	int	fd;

	exec_tree->string = ft_join_all_nexts(exec_tree, status_code, env);
	if (flag == 1)
	{
		if (access(exec_tree->string[0], F_OK) != -1)
			return (-2);
		fd = open(exec_tree->string[0], O_CREAT | O_WRONLY, 0644);
		if (fd == -1)
			return (-1);
	}
	else if (flag == 0)
	{
		if (access(exec_tree->string[0], F_OK) != -1)
		{
			if (access(exec_tree->string[0], W_OK) == -1)
				return (-3);
		}
		fd = open(exec_tree->string[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			return (-1);
	}
	else
		return (open_in_file(exec_tree));
	return (fd);
}

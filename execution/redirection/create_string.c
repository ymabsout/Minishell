/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:49:43 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 03:55:02 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

void	create_string(t_btree *exec_tree, char **string)
{
	int		l_s;
	int		r_s;
	int		i;
	char	**arr;

	l_s = 0;
	r_s = 0;
	while (exec_tree->string[l_s])
		l_s++;
	while (string[r_s])
		r_s++;
	arr = malloc((sizeof(char *) * (l_s + r_s + 1)));
	if (!arr)
		return ;
	i = -1;
	while (++i < l_s + r_s)
	{
		if (i < l_s)
			arr[i] = exec_tree->string[i];
		else
			arr[i] = string[i - l_s];
	}
	arr[i] = NULL;
	free(exec_tree->string);
	exec_tree->string = arr;
}

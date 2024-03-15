/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_single_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 03:48:02 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 03:48:45 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	expand_single_quote(t_btree *exec_tree)
{
	char	*buffer;

	buffer = ft_strtrim(exec_tree->item, "\'");
	free(exec_tree->item);
	exec_tree->item = buffer;
}

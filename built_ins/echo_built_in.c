/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:51:38 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 08:58:33 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static void	printing(int i, int *new_line, char *cmd)
{
	if (i == 1 && !(*new_line))
		return ;
	if (!(*new_line) && find_num_char(cmd, 'n') && \
		find_num_char(cmd, 'n') == ft_strlen(cmd) - 1)
		return ;
	(*new_line) = 1;
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd(" ", 1);
}

int	echo_built_in(char **cmd)
{
	int		new_line;
	int		val;
	int		i;

	val = 1;
	if (!cmd[1])
		return (ft_putstr_fd("\n", 1), 0);
	if (find_num_char(cmd[1], 'n') && \
		find_num_char(cmd[1], 'n') == ft_strlen(cmd[1]) - 1)
	{
		val = 0;
		new_line = 0;
	}
	else
		new_line = 1;
	i = 0;
	while (cmd[++i])
		printing(i, &new_line, cmd[i]);
	if (val)
		write(1, "\n", 1);
	return (0);
}

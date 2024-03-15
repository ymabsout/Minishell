/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:51:38 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 03:25:39 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	echo_built_in(char **cmd)
{
	char	new_line;
	int		i;

	if (!cmd[1])
		return (ft_putstr_fd("\n", 1), 0);
	if (!ft_strncmp(cmd[1], "-n", ft_strlen("-n") + 1))
		new_line = 0;
	else
		new_line = 1;
	i = 0;
	while (cmd[++i])
	{
		if (i == 1 && !new_line)
			continue ;
		ft_putstr_fd(cmd[i], 1);
		ft_putstr_fd(" ", 1);
	}
	if (new_line)
		write(1, "\n", 1);
	return (0);
}

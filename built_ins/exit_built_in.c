/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:53:38 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 03:26:08 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	ft_isdigit(char *str)
{
	while (*str)
		if (!(*str >= '0' && *(str)++ <= '9'))
			return (0);
	return (1);
}

int	exit_built_in(char **cmd, int status_code)
{
	printf("exit\n");
	if (!cmd[1])
		exit(status_code);
	if (!cmd[2])
	{
		if (ft_isdigit(cmd[1]))
			exit(ft_atoi(cmd[1]));
		ft_putstr_fd("BNW: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	ft_putstr_fd("BNW: exit: too many arguments\n", 2);
	return (1);
}

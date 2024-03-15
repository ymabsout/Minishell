/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_failing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:45:24 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 03:23:39 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	sys_failing(int err, char *fn, t_util *s)
{
	if (err != -1)
		return (0);
	if (s)
		s->status_code = 1;
	ft_putstr_fd("BNW: ", 2);
	ft_putstr_fd(fn, 2);
	ft_putstr_fd(": system call failed\n", 2);
	return (1);
}

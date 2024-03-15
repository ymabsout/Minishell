/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:28:45 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 03:36:31 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	pwd_built_in(char **cmd)
{
	char	*path_name;

	if (cmd[1] && cmd[1][0] == '-')
	{
		ft_putstr_fd("pwd: no options are required\n", 2);
		return (1);
	}
	path_name = getcwd(0, 0);
	if (!path_name)
		return (1);
	printf("%s\n", path_name);
	free(path_name);
	return (0);
}

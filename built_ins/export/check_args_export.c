/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:02:04 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 03:35:36 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

static int	check_invalid_plus(char *val, char *cmd, int *is_plus)
{
	if (!val)
	{
		if (cmd[ft_strlen(cmd) - 1] == '=')
			return ((*is_plus = 1), 0);
		else
			return ((*is_plus = 0), 1);
	}
	return ((*is_plus = 1), 0);
}

int	check_args_export(char *cmd, int *is_plus)
{
	int		i;
	char	**arr;

	if (!cmd[0] || !ft_strncmp(cmd, "=", 2))
		return (valid_id_error("export", cmd), 1);
	arr = ft_split(cmd, '=');
	if (!ft_isalpha(arr[0][0]) && arr[0][0] != '_')
		return (valid_id_error("export", cmd), free_double(arr), 1);
	i = 0;
	while (arr[0][++i])
	{
		if (arr[0][i + 1] == '\0' && arr[0][i] == '+')
		{
			if (check_invalid_plus(arr[1], cmd, is_plus))
				return (valid_id_error("export", cmd), free_double(arr), 1);
			else
				continue ;
		}
		if (!ft_isalnum(arr[0][i]) && arr[0][i] != '_')
			return (valid_id_error("export", cmd), free_double(arr), 1);
	}
	return (free_double(arr), 0);
}

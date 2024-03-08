/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:53:38 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/07 17:29:12 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int exit_built_in(char **cmd, int status_code)
{
    printf("exit\n");
    if (!cmd[1])
        exit(status_code);
    if (!cmd[2])
        exit(ft_atoi(cmd[1]));
    ft_putstr_fd("exit: too many arguments\n", 2);
    return (1);
}
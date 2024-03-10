/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:30:50 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/09 19:37:38 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int export_built_in(char **cmd, t_listt **head_env)
{
    int status_code;
    int i;
    int is_plus;

    status_code = 0;
    if (!cmd[1])
        return (export_no_args(*head_env), status_code);
    if (cmd[1][0] == '-')
        return (ft_putstr_fd("export: no options required\n", 2), 1);
    i = 0;
    is_plus = 0;
    while (cmd[++i])
    {
        if (check_args_export(cmd[i], &is_plus))
        {
            status_code = 1;
            continue ;
        }
        if (is_plus)
            (export_plus(head_env, cmd[i]), is_plus = 0);
        else
            export(head_env, cmd[i]);
    }
    return (status_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 21:34:58 by ymabsout          #+#    #+#             */
/*   Updated: 2024/03/07 20:19:04 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void *get_quotes(t_list **root, char *cmd, int index)
{
    t_data_q    track;

    index = 0;
    ft_memset(&track, 0, sizeof(t_data_q));
    (cmd[index] == '\'') && (track.sgl = 1);
    (cmd[index] == '\"') && (track.dbl = 1);
    while (cmd[++index] && (ft_strchr(cmd, '\'') || ft_strchr(cmd, '\"')))
    {
        if (cmd[index] == '\'' && !track.dbl && track.sgl)
        {
            track.sgl = 0;
            cmd = get_cmd_back(cmd, index, root, token_single_q);
            break ;
        }
        else if (cmd[index] == '\"' && !track.sgl && track.dbl)
        {
            track.dbl = 0;
            cmd = get_cmd_back(cmd, index, root, token_double_q);
            break ;
        }
        update_trackers(cmd, index, &track);
    }
    if (track.sgl || track.dbl)
        return(printf("Syntax Error\n"), free(cmd),  NULL);
    return (cmd);
}

void *get_cmd_back(char *cmd, int index, t_list **root, int type)
{
    char *tmp;
    
    tmp = ft_substr(cmd, 0, index + 1);
    lst_addback(root, lst_new(ft_strdup(tmp)));
    lst_last(*root)->typeofcontent = type;
    free(tmp);
    tmp = ft_substr(cmd, index + 1, ft_strlen(cmd + index));
    free(cmd);
    cmd = ft_strdup(tmp);
    free(tmp);
    return (cmd);
}

void *update_trackers(char *cmd, int index, t_data_q * track)
{
    if (cmd[index] == '\"' && !track->dbl && !track->sgl)
        track->dbl = 1;
    else if (cmd[index] == '\'' && !track->sgl && !track->dbl)
        track->sgl = 1;
    return (track);
}

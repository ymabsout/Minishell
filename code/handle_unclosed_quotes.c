/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unclosed_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:31:30 by smoumni           #+#    #+#             */
/*   Updated: 2024/02/02 19:32:04 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void handle_unclosed_quotes(char *line, int *state)
{
    pid_t pid;

    err_handler((pid = fork()));
    if (!pid)
    {
        if (find_num_char(line, '\'') % 2 != 0)
            syntax_error();
        if (find_num_char(line, '"') % 2 != 0)
            syntax_error();
        exit(0);
    }
    err_handler(waitpid(pid, state, 0));
}
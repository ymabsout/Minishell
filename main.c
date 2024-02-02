/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:06:49 by smoumni           #+#    #+#             */
/*   Updated: 2024/02/02 18:54:27 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void parse_input()
{
    char *line;
    pid_t pid;
    int state;

    line = readline(READLINE_TITLE);
    if (!line)
        return ;
    err_handler((pid = fork()));
    if (!pid)
    {
        if (find_num_char(line, '\'') % 2 != 0)
            syntax_error();
        if (find_num_char(line, '"') % 2 != 0)
            syntax_error();
        exit(0);
    }
    err_handler(waitpid(pid, &state, 0));
    free(expand_env_vars(line, state));
}

void lol()
{
    system("leaks minishell");
}

int main()
{
    // atexit(lol);
    while (1)
        parse_input();
}
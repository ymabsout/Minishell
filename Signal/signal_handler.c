/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:57:42 by ymabsout          #+#    #+#             */
/*   Updated: 2024/03/15 00:11:38 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void handle_ctrl_c()
{
    if (g_received_signal != -1)
        printf("\n");
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    if (!g_received_signal)
        g_received_signal = 2;   
}

void	handle_ctrl_c(int c)
{
	(void)c;
	if (received_signal != -1)
		printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	if (!g_received_signal)
		g_received_signal = 2;
}

void	handle_signal(int c)
{
	(void)c;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_ctrl_c);
}

void	sig_def(int c)
{
    write(STDOUT_FILENO, "\n", 1);
    close(STDIN_FILENO);
    g_received_signal = -1;
}

void no_nl(int c)
{
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    g_received_signal = 2;
}  

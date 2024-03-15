/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_sub_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:41:07 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 00:07:39 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	execute_sub_shell(t_btree *exec_tree, t_listt *env, t_util *s)
{
	pid_t	pid;

	exec_tree->flag_subshell = 0;
	pid = fork();
	if (sys_failing(pid, "fork", s))
		return ;
	if (pid > 0)
	{
		s->pid = pid;
		return ;
	}
	executing(exec_tree, env, s);
	if (exec_tree->pipe_read_end != 0)
		close(exec_tree->pipe_read_end);
	if (exec_tree->pipe_write_end != 0)
		close(exec_tree->pipe_write_end);
	if (waitpid(s->pid, &s->status_code, 0) != -1)
		s->status_code = WEXITSTATUS(s->status_code);
	while (waitpid(-1, 0, 0) != -1)
		;
	exit(s->status_code);
}

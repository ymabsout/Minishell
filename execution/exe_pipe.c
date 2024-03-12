/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:40:04 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/12 18:04:00 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static void	exe_left(t_btree *exec_tree, t_listt *env, s_lol *s, int fd)
{
	pid_t	pid;

	pid = fork();
	if (sys_failing(pid, "fork", s))
		return ;
	if (!pid)
	{
		if (exec_tree->pipe_write_end)
			close(exec_tree->pipe_write_end);
		close(fd);
		executing(exec_tree->left, env, s);
		if (waitpid(s->pids, &s->status_code, 0) != -1)
			s->status_code = WEXITSTATUS(s->status_code);
		while (wait(0) != -1)
			;
		exit(s->status_code);
	}
}

static void	exe_right(t_btree *exec_tree, t_listt *env, s_lol *s, int fd)
{
	pid_t	pid;

	exec_tree->pipe_read_end = fd;
	exec_tree->stdin = fd;
	pid = fork();
	if (sys_failing(pid, "fork", s))
		return ;
	if (!pid)
	{
		executing(exec_tree, env, s);
		if (waitpid(s->pids, &s->status_code, 0) != -1)
			s->status_code = WEXITSTATUS(s->status_code);
		while (wait(0) != -1)
			;
		exit(s->status_code);
	}
	s->pids = pid;
}

void	execute_pipe(t_btree *exec_tree, t_listt *env, s_lol *s)
{
	int	fd[2];

	if (sys_failing(pipe(fd), "pipe", s))
		return ;
	if (exec_tree->pipe_write_end)
		exec_tree->stdout = exec_tree->pipe_write_end;
	exec_tree->left->stdout = fd[1];
	exec_tree->left->pipe_write_end = fd[1];
	exe_left(exec_tree, env, s, fd[0]);
	exec_tree->right->stdout = exec_tree->stdout;
	exec_tree->right->pipe_write_end = fd[1];
	exe_right(exec_tree->right, env, s, fd[0]);
	if (exec_tree->pipe_read_end)
		close(exec_tree->pipe_read_end);
	if (exec_tree->pipe_write_end)
		close(exec_tree->pipe_write_end);
	close(fd[0]);
	close(fd[1]);
}

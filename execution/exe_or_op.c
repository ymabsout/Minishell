/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_or_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:38:27 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 06:27:24 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	execute_or_op(t_btree *exec_tree, t_listt **env, t_util *s)
{
	if (exec_tree->pipe_write_end && exec_tree->pipe_read_end)
	{
		exec_tree->left->pipe_write_end = exec_tree->pipe_write_end;
		exec_tree->left->pipe_read_end = exec_tree->pipe_read_end;
	}
	exec_tree->left->stdin = exec_tree->stdin;
	exec_tree->left->stdout = exec_tree->stdout;
	executing(exec_tree->left, env, s);
	if (waitpid(s->pid, &s->status_code, 0) != -1)
		s->status_code = WEXITSTATUS(s->status_code);
	while (waitpid(-1, 0, 0) != -1)
		;
	if (s->status_code != 0)
	{
		if (exec_tree->pipe_write_end && exec_tree->pipe_read_end)
		{
			exec_tree->right->pipe_write_end = exec_tree->pipe_write_end;
			exec_tree->right->pipe_read_end = exec_tree->pipe_read_end;
		}
		exec_tree->right->stdin = exec_tree->stdin;
		exec_tree->right->stdout = exec_tree->stdout;
		executing(exec_tree->right, env, s);
	}
}

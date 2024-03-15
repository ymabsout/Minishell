/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:24:05 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 07:55:36 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	run_built_in(char **str, t_listt **env, int status_code, int flag)
{
	if (flag == 0)
		return (echo_built_in(str));
	else if (flag == 1)
		return (cd_built_in(str, env));
	else if (flag == 2)
		return (pwd_built_in(str));
	else if (flag == 3)
		return (export_built_in(str, env));
	else if (flag == 4)
		return (unset_built_in(str, env));
	else if (flag == 5)
		return (env_built_in(str, *env));
	return (exit_built_in(str, status_code));
}

static int	duping(int *in, int *out, t_btree *exec_tree, t_util *s)
{
	*in = dup(STDIN_FILENO);
	*out = dup(STDOUT_FILENO);
	if (sys_failing(*in, "dup", s))
		return (1);
	if (sys_failing(*out, "dup", s))
		return (1);
	if (sys_failing(dup2(exec_tree->stdin, STDIN_FILENO), "dup2", s))
		return (1);
	if (sys_failing(dup2(exec_tree->stdout, STDOUT_FILENO), "dup2", s))
		return (1);
	return (0);
}

static void	execute(t_btree *exec_tree, t_listt **env, t_util *s, int flag)
{
	int	in;
	int	out;

	if (duping(&in, &out, exec_tree, s))
		return ;
	if (exec_tree->stdin != 0)
		close(exec_tree->stdin);
	if (exec_tree->stdout != 1)
		close(exec_tree->stdout);
	if (exec_tree->pipe_read_end != 0)
		close(exec_tree->pipe_read_end);
	if (exec_tree->pipe_write_end != 0)
		close(exec_tree->pipe_write_end);
	s->status_code = run_built_in(exec_tree->string, env, \
		s->status_code, flag);
	if (sys_failing(dup2(in, STDIN_FILENO), "dup2", s))
		return ;
	if (sys_failing(dup2(out, STDOUT_FILENO), "dup2", s))
		return ;
}

int	execute_built_in(t_btree *exec_tree, t_listt **env, t_util *s)
{
	if (!ft_strncmp(exec_tree->string[0], "echo", 5))
		return (execute(exec_tree, env, s, 0), 1);
	else if (!ft_strncmp(exec_tree->string[0], "cd", 3))
		return (execute(exec_tree, env, s, 1), 1);
	else if (!ft_strncmp(exec_tree->string[0], "pwd", 4))
		return (execute(exec_tree, env, s, 2), 1);
	else if (!ft_strncmp(exec_tree->string[0], "export", 7))
		return (execute(exec_tree, env, s, 3), 1);
	else if (!ft_strncmp(exec_tree->string[0], "unset", 6))
		return (execute(exec_tree, env, s, 4), 1);
	else if (!ft_strncmp(exec_tree->string[0], "env", 4))
		return (execute(exec_tree, env, s, 5), 1);
	else if (!ft_strncmp(exec_tree->string[0], "exit", 5))
		return (execute(exec_tree, env, s, 6), 1);
	return (0);
}

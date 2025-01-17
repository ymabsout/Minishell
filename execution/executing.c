/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:12:37 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 07:27:48 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static void	redirect_streams(t_btree *node)
{
	if (node->stdout == 0)
		node->stdout = 1;
	if (node->stderr == 0)
		node->stderr = 2;
}

void	executing(t_btree *exec_tree, t_listt **env, t_util *s)
{
	redirect_streams(exec_tree);
	if (exec_tree->flag_subshell)
		execute_sub_shell(exec_tree, env, s);
	else if (exec_tree->type & token_ampersand)
		execute_and_op(exec_tree, env, s);
	else if (exec_tree->type & token_or)
		execute_or_op(exec_tree, env, s);
	else if (exec_tree->type & token_pipe)
		execute_pipe(exec_tree, env, s);
	else if (exec_tree->type & token_red_here_doc)
		execute_red(exec_tree, env, s, 3);
	else if (exec_tree->type & token_red_input)
		execute_red(exec_tree, env, s, 2);
	else if (exec_tree->type & token_red_out_trunc)
		execute_red(exec_tree, env, s, 1);
	else if (exec_tree->type & token_red_out_append)
		execute_red(exec_tree, env, s, 0);
	else if (exec_tree->type & (token_word | \
		token_single_q | token_double_q))
		execute_cmd(exec_tree, env, s);
}

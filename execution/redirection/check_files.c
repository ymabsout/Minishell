/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:12:19 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 06:42:58 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

static void	free_unlink(t_listt *l, int flag)
{
	t_listt	*c;
	t_listt	*next;

	c = l;
	while (c)
	{
		if (flag && \
			((t_btree *)(c->content))->typeofcontent & token_red_out_trunc)
			unlink(((t_btree *)(c->content))->right->string[0]);
		free_double(((t_btree *)(c->content))->right->string);
		((t_btree *)(c->content))->right->string = 0;
		next = c->next;
		free(c);
		c = next;
	}
}

static int	checking(t_listt *l, t_util *s, t_listt **env)
{
	int		fd;
	t_listt	*c;

	c = l;
	while (c)
	{
		if (((t_btree *)(c->content))->typeofcontent & \
			(token_red_input | token_red_here_doc))
			fd = open_file(((t_btree *)(c->content))->right, 2, \
				s->status_code, env);
		else if (((t_btree *)(c->content))->typeofcontent & token_red_out_trunc)
			fd = open_file(((t_btree *)(c->content))->right, 1, \
				s->status_code, env);
		else if (((t_btree *)(c->content))->typeofcontent & \
			token_red_out_append)
			fd = open_file(((t_btree *)(c->content))->right, 0, \
				s->status_code, env);
		if (fd < 0)
			return (fd_failure(((t_btree *)(c->content))->right->string[0], \
				fd, s), free_unlink(l, 0), 1);
		close(fd);
		c = c->next;
	}
	free_unlink(l, 1);
	return (0);
}

static int	check_files(t_btree *exec_tree, t_util *s, t_listt **env)
{
	t_btree	*curr;
	t_listt	*l;

	l = 0;
	ft_lstadd_front(&l, ft_lstnew(exec_tree));
	curr = exec_tree->left;
	while (curr && curr->typeofcontent & token_red)
	{
		ft_lstadd_front(&l, ft_lstnew(curr));
		curr = curr->left;
	}
	return (checking(l, s, env));
}

void	redirecting_pipe(t_btree *exec_tree)
{
	char	*file;

	if (exec_tree->pipe_write_end && exec_tree->pipe_read_end)
	{
		exec_tree->left->pipe_write_end = exec_tree->pipe_write_end;
		exec_tree->left->pipe_read_end = exec_tree->pipe_read_end;
	}
	file = exec_tree->right->string[0];
	free(file);
}

int	into_files(int *i, t_btree *exec_tree, t_util *s, t_listt **env)
{
	if (!*i)
	{
		*i = -1;
		if (check_files(exec_tree, s, env))
			return ((*i = 0), 1);
	}
	return (0);
}

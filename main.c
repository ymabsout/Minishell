/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:30:20 by ymabsout          #+#    #+#             */
/*   Updated: 2024/03/15 07:12:36 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	dl(void *content)
{
	free((char *)content);
}

void	kept_exec(t_btree *exec_tree, t_util *s, t_listt **root_env)
{
	return_def(0);
	executing(exec_tree, root_env, s);
	free_tree(exec_tree);
	sig_def(0);
	if (waitpid((*s).pid, &s->status_code, 0) != -1)
	{
		if (WIFSIGNALED((*s).status_code))
		{
			(*s).status_code = WTERMSIG((*s).status_code) + 128;
			if ((*s).status_code == 131)
				printf("Quit: %d\n", WTERMSIG((*s).status_code));
			else if ((*s).status_code == 130)
				printf("\n");
		}
		else
			(*s).status_code = WEXITSTATUS((*s).status_code);
	}
}

void	exec_st(t_listt **root_env, t_btree *exec_tree, t_util *s, char *keep)
{
	while (keep && keep[0])
	{
		add_history(keep);
		exec_tree = (t_btree *)parsing(keep);
		if (!exec_tree && keep[0] != '\0')
			(printf("Parsing Error\n"), (*s).status_code = 258);
		if (exec_tree)
		{
			g_received_signal = 0;
			get_here_doc(exec_tree, (*s).status_code, (*root_env));
			if (g_received_signal == -1)
			{
				(*s).status_code = 1;
				break ;
			}
			kept_exec(exec_tree, s, root_env);
			while (waitpid(-1, 0, 0) != -1)
				;
		}
		g_received_signal = 0;
		break ;
	}
	free(keep);
}

int	start_minishell(char **env)
{
	char	*input;
	char	*keep;
	t_btree	*exec_tree;
	t_util	s;
	t_listt	*root_env;

	exec_tree = NULL;
	root_env = create_envs(env);
	while (1)
	{
		handle_signal(0);
		input = readline(">_: ");
		if (g_received_signal == 2)
		{
			g_received_signal = 0;
			s.status_code = 1;
		}
		if (!input)
			return (printf("exit\n"), \
				ft_lstclear(&root_env, dl), s.status_code);
		keep = ft_strtrim(input, " ");
		exec_st(&root_env, exec_tree, &s, keep);
		free(input);
	}
}

int	main(int ac, char *av[], char **env)
{
	(void)av;
	if (ac != 1)
		return (printf("error arguments\n"), 0);
	setterm();
	return (start_minishell(env));
}

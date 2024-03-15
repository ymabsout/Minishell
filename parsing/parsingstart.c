/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingstart.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 07:09:12 by ymabsout          #+#    #+#             */
/*   Updated: 2024/03/15 07:28:54 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	*parsing(char *input)
{
	char	*cmd;
	t_list	*saved_list;
	t_list	*cleared_list;
	t_btree	*rootoftree;

	if (!input[0])
		return (NULL);
	cmd = ft_strdup(input);
	saved_list = tokenize_lex(cmd);
	if (!saved_list)
		return (NULL);
	cleared_list = repair_list(saved_list);
	if (!cleared_list)
		return (lst_clear(&saved_list), NULL);
	lst_clear(&saved_list);
	saved_list = cleared_list;
	rootoftree = parse_ampersand_or(&cleared_list);
	if (!rootoftree)
		return (lst_clear(&saved_list), NULL);
	lst_clear(&saved_list);
	return (rootoftree);
}

void	setterm(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag = ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	get_here_doc(t_btree *exec_tree, int status, t_listt *env)
{
	if (!exec_tree)
		return ;
	get_here_doc(exec_tree->left, status, env);
	if (exec_tree->type & token_red_here_doc)
		read_stdin(exec_tree, status, env);
	get_here_doc(exec_tree->right, status, env);
}

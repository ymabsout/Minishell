/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:12 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 00:07:29 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	*get_file(void)
{
	int		*index;
	char	*indexfile;
	char	*file_to_open;

	index = malloc(sizeof(int) * 1);
	if (!index)
		return (NULL);
	indexfile = ft_itoa((unsigned long)index);
	free(index);
	file_to_open = ft_strjoin("/tmp/", indexfile);
	free(indexfile);
	return (file_to_open);
}

static t_btree	*lstnew(char *content)
{
	t_btree	*new_list;

	new_list = (t_btree *)malloc(sizeof(t_btree));
	if (!new_list)
		return (NULL);
	ft_memset(new_list, 0, sizeof(t_btree));
	new_list->item = ft_strdup(content);
	return (new_list);
}

void	routine_heredoc(int fd, t_btree *exec_tree, \
	int status_code, t_listt *env)
{
	char	*str;
	char	*line;
	t_btree	*l;
	int		expand_or_not;

	if (exec_tree->typeofcontent & (token_double_q | token_single_q) || \
		exec_tree->down)
		expand_or_not = 0;
	else
		expand_or_not = 1;
	while (!g_received_signal && isatty(STDIN_FILENO))
	{
		signal(SIGINT, heredoc_signal);
		line = readline("> ");
		if (!line || \
			!ft_strncmp(line, exec_tree->item, ft_strlen(exec_tree->item) + 1))
			break ;
		l = lstnew(line);
		if (expand_or_not)
			expand_dollar_sign(l, status_code, env);
		str = ft_strjoin(l->item, "\n");
		(free(line), free(l->item), free(l));
		(write(fd, str, ft_strlen(str)), free(str));
	}
	free(line);
}

void	read_stdin(t_btree *exec_tree, int status_code, t_listt *env)
{
	int		fd;
	char	*filetoconvert;
	int		fd1_copy_0;

	if (g_received_signal != -1)
	{
		fd1_copy_0 = dup(STDIN_FILENO);
		filetoconvert = (char *)get_file();
		unlink(filetoconvert);
		fd = open(filetoconvert, O_CREAT | O_WRONLY, 0644);
		if (fd < 0)
			return ;
		exec_tree->right->item = ft_join_alldowns_heredoc(exec_tree->right);
		routine_heredoc(fd, exec_tree->right, status_code, env);
		exec_tree->right->down = NULL;
		close(fd);
		free(exec_tree->right->item);
		exec_tree->right->item = ft_strdup(filetoconvert);
		dup2(fd1_copy_0, STDIN_FILENO);
		close(fd1_copy_0);
		free(filetoconvert);
	}
}

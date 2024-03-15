/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:27:03 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 03:25:14 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static void	insert_new_env(t_listt **head_env, char *key, char *val)
{
	t_listt	*node;
	char	*content;

	content = ft_strjoin(key, val);
	if (!content)
		exit(-1);
	node = ft_lstnew(content);
	if (!node)
		exit(-1);
	ft_lstadd_back(head_env, node);
}

static void	old_pwd_fn(int is_old_pwd, t_listt **head_env, char *old_pwd)
{
	if (!is_old_pwd)
		insert_new_env(head_env, "OLDPWD=", old_pwd);
}

static void	mutate_env_dirs(char *new_pwd, char *old_pwd, t_listt **head_env)
{
	t_listt	*curr;
	int		is_old_pwd;

	curr = *head_env;
	is_old_pwd = 0;
	while (curr)
	{
		if (!ft_strncmp(curr->content, "PWD", 3))
		{
			free((char *)(curr->content));
			curr->content = ft_strjoin("PWD=", new_pwd);
			if (!curr->content)
				return (perror("malloc: "));
		}
		if (!ft_strncmp(curr->content, "OLDPWD", 6))
		{
			is_old_pwd = 1;
			free((char *)(curr->content));
			curr->content = ft_strjoin("OLDPWD=", old_pwd);
			if (!curr->content)
				return (perror("malloc: "));
		}
		curr = curr->next;
	}
	old_pwd_fn(is_old_pwd, head_env, old_pwd);
}

int	cd_built_in(char **cmd, t_listt **head_env)
{
	char	*w_dir;
	char	*c_dir;

	w_dir = getcwd(0, 0);
	if (!w_dir)
		return (1);
	if (chdir(cmd[1]) == -1)
	{
		ft_putstr_fd("BNW: cd: ", 2);
		perror(cmd[1]);
		return (1);
	}
	c_dir = getcwd(0, 0);
	if (!c_dir)
		return (free(w_dir), 1);
	printf("%s\n", c_dir);
	mutate_env_dirs(c_dir, w_dir, head_env);
	free(w_dir);
	free(c_dir);
	return (0);
}

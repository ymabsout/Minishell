/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:03:19 by ymabsout          #+#    #+#             */
/*   Updated: 2024/02/13 19:06:56 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m1.h"

void buildtree(t_cms *fs)
{
	fs->i = -1;
	while (fs->meta[++fs->i])
		btree_insert_data(&fs->root, (char *)fs->meta[fs->i]);
	fs->i = -1;
	while (fs->com[++fs->i])
		btree_insert_data(&fs->root, (char *)fs->com[fs->i]);
	while (fs->root != NULL)
	{
		printf("metacharacter : %s\n", (char*)fs->root->item);
		if (fs->root->left)
			printf("command in left node %s\n", (char*)fs->root->left->item);
		fs->root = fs->root->right;
	}
}

void splitcmds(t_cms *infs, char **cmd)
{
	while (cmd[++infs->i])
	{
		if (!ft_strncmp(cmd[infs->i], "<", 1) || !ft_strncmp(cmd[infs->i], ">", 1) \
			 || !ft_strncmp(cmd[infs->i], "|", 1))
			infs->meta[++infs->j] = ft_strdup(cmd[infs->i]);
		else
			infs->com[++infs->k] = ft_strdup(cmd[infs->i]);
	}
	infs->meta[++infs->j] = NULL;
	infs->com[++infs->k] = NULL;
}

void *checkcmds(char **cmd, char *str, int count)
{
	t_cms *infs;
	
	infs = malloc(sizeof(t_cms));
	if (!infs)
		return (NULL);
	infs->red = 0;
	infs->i = -1;
	infs->j = -1;
	infs->k = -1;
	infs->s = str;
	infs->root = NULL;
	if (!ft_strchr(str, '>'))
		infs->red = 1;
	infs->meta = malloc((sizeof(char *) * count) + 1);
	infs->com = malloc(sizeof(char *) * count + 2);
	if (!infs->meta || !infs->com)
		return (NULL);
	splitcmds(infs, cmd);
	buildtree(infs);
	return (infs);
}

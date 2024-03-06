/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:43:22 by ymabsout          #+#    #+#             */
/*   Updated: 2024/03/06 00:14:57 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void *cmd_parse(t_list **root, t_list **new_list, int *track)
{
	if ((*root)->typeofcontent & (token_word | token_quote))
	{
		if (lst_last((*new_list)) && lst_last((*new_list))->typeofcontent & token_par_out)
			return (printf("Syntax error near \'%s'\n", (*root)->content), lst_clear(new_list), NULL);
		if ((*track) || lst_last((*new_list))->typeofcontent & token_meta)
			lst_addback(new_list, duplicate_node((*root)));
		else
			lst_add_down(new_list, duplicate_node((*root)));
		(*track) = 0;
	}
	else if ((*root)->typeofcontent & token_space)
		(*track) = 1;
	return ((*new_list));
}

void *meta_cmd_parser(t_list **root, t_list **new_list, int *track)
{
	if ((*root)->typeofcontent & token_meta)
	{
		if ((*new_list) && (*root)->typeofcontent & token_red && lst_last((*new_list))->typeofcontent & token_and_or)
			;
		else if (((*new_list) && lst_last((*new_list))->typeofcontent & (token_red | token_and_or)) \
			|| ((*new_list) && lst_last((*new_list))->typeofcontent & token_pipe \
			&& (*root)->typeofcontent & token_pipe) || !(*root)->next \
			|| (!(*new_list) && (*root)->typeofcontent & (token_pipe | token_and_or)))
			return (printf("Syntax error near %s\n", (*root)->content), lst_clear(new_list),  NULL);
		lst_addback(new_list, duplicate_node((*root)));
		if (!(*track))
			(*track) = 1;
	}
	else 
		if (!cmd_parse(root, new_list, track))
			return (NULL);
	return((*new_list));
}

void	*type_parser(t_list **root, t_list **new_list, int *track, int *pth)
{
	if ((*root)->typeofcontent & token_pth)
	{
		if ((lst_last((*new_list)) && (lst_last((*new_list))->typeofcontent & token_par_out) && ((*root)->typeofcontent & token_par_in)) \
    		|| (((*root)->typeofcontent & token_par_in) && !(lst_last((*new_list))->typeofcontent & (token_pipe | token_and_or))))
			return (printf("syntax error neagr \'%s'\n", (*root)->content),  lst_clear(new_list), NULL);
		lst_addback(new_list, duplicate_node((*root)));
		if ((*root)->typeofcontent & token_par_in)
			(*pth)++;
		else if ((*root)->typeofcontent & token_par_out)
			(*pth)--;
	}
	else
		if (!meta_cmd_parser(root, new_list, track))
			return (NULL);
	return ((*new_list));
}

t_list	*repair_list(t_list *root)
{
	t_list	*new_list;
	int		track;
	int		pth_track;

	pth_track = 0;
	track = 1;
	new_list = NULL;
	while (root)
	{
		if (!type_parser(&root, &new_list, &track, &pth_track))
			return (NULL);
		root = root->next;
	}
	if (pth_track != 0)
		return (lst_clear(&new_list), NULL);
	return (new_list);
}

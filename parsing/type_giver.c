/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_giver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 21:37:14 by ymabsout          #+#    #+#             */
/*   Updated: 2024/03/14 21:52:07 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	*set_correct_follow(t_list *root, int numb)
{
	if (ft_strchr(root->content, '\"'))
		root->type = token_double_q;
	else if (ft_strchr(root->content, '\''))
		root->type = token_single_q;
	else if (ft_strchr(root->content, '|'))
	{
		if (numb == 2)
			root->type = token_or;
		else
			root->type = token_pipe;
	}
	else if (ft_strchr(root->content, ' ') || ft_strchr(root->content, '\t'))
		root->type = token_space;
	else
		root->type = token_word;
	return (root);
}

void	*set_correct_type(t_list *root, int numb)
{
	if (!ft_strncmp(root->content, "&&", 2))
		root->type = token_ampersand;
	else if (!ft_strncmp(root->content, "(", 1))
		root->type = token_par_in;
	else if (!ft_strncmp(root->content, ")", 1))
		root->type = token_par_out;
	else if (ft_strchr(root->content, '<'))
	{
		if (numb == 2)
			root->type = token_red_here_doc;
		else
			root->type = token_red_input;
	}
	else if (ft_strchr(root->content, '>'))
	{
		if (numb == 2)
			root->type = token_red_out_append;
		else
			root->type = token_red_out_trunc;
	}
	else
		root = set_correct_follow(root, numb);
	return (root);
}

int	db_sl_quote(int c)
{
	return (c == '\'' || c == '\"');
}

int	delimeter(int c)
{
	return (c == '&' || c == '|' || c == '>' \
		|| c == '<' || c == '\0' || c == ')' \
		|| c == '(');
}

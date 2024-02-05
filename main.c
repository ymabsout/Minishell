/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:30:20 by ymabsout          #+#    #+#             */
/*   Updated: 2024/02/05 17:31:28 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m1.h"

void *set_correct_type(t_list *root)
{
    if (ft_strchr(root->content, '<'))
        root->typeofcontent = token_red_input;
    else if (ft_strchr(root->content, '>'))
        root->typeofcontent = token_red_out_trunc;
    else if (ft_strchr(root->content, '|'))
        root->typeofcontent = token_pipe;
    else if (ft_strchr(root->content, ' '))
        root->typeofcontent = token_space;
    else
        root->typeofcontent = token_word;
    return (root);
}

void printlist(t_list *root)
{
    while (root)
    {
        printf("{%s} --> type :{%d}\n", root->content, root->typeofcontent);
        root = root->next;
    }
}
void *tokenize_lex(char *cmd)
{
    t_list *root;
    int index;
    char *keeper;
    t_list *holder;

    root = NULL;
    index = 0;
    while (cmd[index])
    {
        if (cmd[index] == ' ')
        {
            keeper = ft_strdup(" ");
            holder = lst_new(keeper);
            lst_addback(&root, set_correct_type(lst_new(keeper)));
            while (cmd[index] && cmd[index] == ' ')
                index++;
            cmd = ft_substr(cmd, index, ft_strlen(cmd));
            index = 0;
        }
        while (cmd[index] && cmd[index] != ' ')
            index++;
        keeper = ft_substr(cmd, 0, index); 
        holder = lst_new(keeper);
        holder = set_correct_type(holder);
        lst_addback(&root, holder);
    }
    printlist(root);
    // cmd = ft_substr(cmd, index, ft_strlen(cmd));
}

void *parsing(char *input)
{
    char *cmd;
    t_list *saved_list;

    cmd = ft_strtrim(ft_strdup(input), " ");
    if (!cmd)
        return (NULL);
    saved_list = tokenize_lex(cmd);
    if (!saved_list)
        return (NULL);
    return (cmd);
}


int main (int ac, char *av[], char **env)
{
    if (ac != 1)
        return (printf("error arguments\n"), 0);
    (void)av;
    char *input = readline("Minishell:");
    while (input)
    {
        if (!parsing(input))
            printf("Parsing Error\n");
        add_history(input);
        input = readline("Minishell:");
    }
}
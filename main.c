/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:30:20 by ymabsout          #+#    #+#             */
/*   Updated: 2024/02/06 17:09:32 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m1.h"

int delimeter(int c)
{
    if (c == '|' || c == '>' || c == '<' || c == '\0')
        return (0);
    else
        return (1);
}

void *set_correct_type(t_list *root, int numb)
{
    if (ft_strchr(root->content, '<'))
    {
        if (numb == 2)
            root->typeofcontent = token_red_here_doc;
        else
            root->typeofcontent = token_red_input;
    }
    else if (ft_strchr(root->content, '>'))
    {
        if (numb == 2)
            root->typeofcontent = token_red_out_append;
        else
            root->typeofcontent = token_red_out_trunc;
    }
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

void *handle_special_char(char *cmd, int *indx, t_list **root)
{
    if (cmd[(*indx)] == '<')
    {
        if (cmd[(*indx) + 1] == '<')
        {
            lst_addback(root, set_correct_type(lst_new("<<"), 2));
            cmd = ft_substr(cmd, (*indx) + 1, ft_strlen(cmd));
        }
        else
        {
            lst_addback(root, set_correct_type(lst_new("<"), 1));
            cmd = ft_substr(cmd, (*indx), ft_strlen(cmd));
        }
    }
    else if (cmd[(*indx)] == '>')
    {
         if (cmd[(*indx) + 1] == '>')
        {
            lst_addback(root, set_correct_type(lst_new(">>"), 2));
            cmd = ft_substr(cmd, (*indx) + 1, ft_strlen(cmd));
        }
        else
        {
            lst_addback(root, set_correct_type(lst_new(">"), 1));
            cmd = ft_substr(cmd, (*indx), ft_strlen(cmd));
        }
    }
    return (cmd);
}

void *tokenize_lex(char *cmd)
{
    t_list *root;
    int index;
    char *keeper;
    t_list *holder;
    int track = 0;

    root = NULL;
    index = -1;
    while (++index <= ft_strlen(cmd))
    {
        if (cmd[index] == ' ' || cmd[index] == '\t')
        {
            if (index != 0)
                lst_addback(&root, (t_list*)set_correct_type(lst_new(ft_substr(cmd, 0 , index)), 1));
            lst_addback(&root, set_correct_type(lst_new(ft_strdup(" ")), 1));
            while (cmd[index] && cmd[index] == ' ')
                index++;
            cmd = ft_strdup(cmd + index);
            index = -1;
        }
        else if (!delimeter(cmd[index]))
        {
            if (index  != 0)
                lst_addback(&root, set_correct_type(lst_new(ft_substr(cmd, 0, index)), 1));
            if (cmd[index] != '\0')
                lst_addback(&root, (t_list *)set_correct_type(lst_new(ft_substr(cmd, index, 1)), 1));
            if (index != ft_strlen(cmd))
            {
                cmd = ft_strdup(cmd + index + 1);
                index = -1;
            }
        }
    }
    printlist(root);
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
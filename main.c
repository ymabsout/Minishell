/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:30:20 by ymabsout          #+#    #+#             */
/*   Updated: 2024/03/01 01:38:45 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int delimeter(int c)
{
    return (c == '&' ||c == '|' || c == '>' \
        || c == '<' || c == '\0' || c == ')' \
        || c == '(');
}

void *set_correct_follow(t_list *root, int numb)
{
    if (ft_strchr(root->content, '\"'))
        root->typeofcontent = token_double_q;
    else if (ft_strchr(root->content, '\''))
        root->typeofcontent = token_single_q;
    else if (ft_strchr(root->content, '|'))
    {
        if (numb == 2)
            root->typeofcontent = token_or;
        else
            root->typeofcontent = token_pipe;
    }
    else if (ft_strchr(root->content, ' '))
        root->typeofcontent = token_space;
    else
        root->typeofcontent = token_word;
    return (root);
}
void *set_correct_type(t_list *root, int numb)
{
    if (!ft_strncmp(root->content, "&&", 2))
        root->typeofcontent = token_ampersand;
    else if (!ft_strncmp(root->content, "(", 1))
        root->typeofcontent = token_par_in;
    else if (!ft_strncmp(root->content, ")", 1))
        root->typeofcontent = token_par_out;
    else if (ft_strchr(root->content, '<'))
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
    else 
        root = set_correct_follow(root, numb);
    return (root);
}

void printdownlist(t_list *root)
{
    while (root)
    {
        printf("^^^^^down level ->{%s} --> type :{%d}^^^^\n", root->content, root->typeofcontent);
        root = root->down;
    }
}

void printlist(t_list *root, int a)
{
    t_list *holder;
    if (a == 1)
    {
        while (root)
        {
            printf("{%s} --> type :{%d}\n",  root->content, root->typeofcontent);
            holder = root;
            if (root->down)
                printdownlist(root->down);
            root = root->next;
        }
    }
    while (root)
    {
        printf("{%s} --> type :{%d}\n",  root->content, root->typeofcontent);
        root = root->next;
    }
}

int db_sl_quote(int c)
{
    return (c == '\'' || c == '\"');
}

void *get_cmd_back(char *cmd, int index, t_list **root, int type)
{
    char *tmp;
    
    tmp = ft_substr(cmd, 0, index + 1);
    lst_addback(root, lst_new(ft_strdup(tmp)));
    lst_last(*root)->typeofcontent = type;
    free(tmp);
    tmp = ft_substr(cmd, index + 1, ft_strlen(cmd + index));
    free(cmd);
    cmd = ft_strdup(tmp);
    free(tmp);
    return (cmd);
}

void update_trackers(char *cmd, int index, t_data_q * track)
{
    if (cmd[index] == '\"' && !track->dbl && !track->sgl)
        track->dbl = 1;
    else if (cmd[index] == '\'' && !track->sgl && !track->dbl)
        track->sgl = 1;
}
void *get_quotes(t_list **root, char *cmd, int index)
{
    t_data_q    track;

    ft_memset(&track, 0, sizeof(t_data_q));
    (cmd[index] == '\'') && (track.sgl = 1);
    (cmd[index] == '\"') && (track.dbl = 1);
    index = 0;
    while (cmd[++index] && (ft_strchr(cmd, '\'') || ft_strchr(cmd, '\"')))
    {
        if (cmd[index] == '\'' && !track.dbl && track.sgl)
        {
            track.sgl = 0;
            cmd = get_cmd_back(cmd, index, root, token_single_q);
            break ;
        }
        else if (cmd[index] == '\"' && !track.sgl && track.dbl)
        {
            track.dbl = 0;
            cmd = get_cmd_back(cmd, index, root, token_double_q);
            break ;
        }
        update_trackers(cmd, index, &track);
    }
    if (track.sgl || track.dbl)
        return(printf("Syntax Error\n"), NULL);
    return (cmd);
}

void *tokenize_lex(char *cmd)
{
    t_list *root;
    int index;
    char *tmp;
    int track;
    int savepos;

    track = 0;
    savepos = 0;
    root = NULL;
    index = -1;
    while (++index <= ft_strlen(cmd))
    {
        if (cmd[index] == ' ' || cmd[index] == '\t')
        {
            if (index != 0)
            {
                tmp = ft_substr(cmd, 0, index--);
                lst_addback(&root, set_correct_type(lst_new(ft_strdup(tmp)), 1));
                free(tmp);
            }
            lst_addback(&root, set_correct_type(lst_new(ft_strdup(" ")), 1));
            while (cmd[++index] && cmd[index] == ' ')
                ;
            tmp = ft_substr(cmd ,index, ft_strlen(cmd + index));
            free(cmd);
            cmd = ft_strdup(tmp);
            free(tmp);
            index = -1;
        }
        else if (delimeter(cmd[index]))
        {
            if (index  != 0)
            {
                tmp = ft_substr(cmd, 0, index);
                lst_addback(&root, set_correct_type(lst_new(ft_strdup(tmp)), 1));
                free(tmp);
            }
            if (cmd[index] != '\0')
            {
                if (cmd[index] == '&')
                {
                    if (cmd[index] == cmd[index + 1])
                        lst_addback(&root, set_correct_type(lst_new(ft_strdup("&&")), 2));
                    else
                        return (printf("syntax error near %c\n", cmd[index]), NULL);
                    track = 1;
                }
                else if (delimeter(cmd[index + 1]) && cmd[index + 1] != ')' && cmd[index + 1] != '(')
                {
                    if ((cmd[index] == '|' && cmd[index + 1] != cmd[index]) || cmd[index] != cmd[index + 1])
                    {
                        tmp = ft_substr(cmd, index, 1);
                        lst_addback(&root, set_correct_type(lst_new(ft_strdup(tmp)), 1));
                        track = 0;
                    }
                    else
                    {
                        tmp = ft_substr(cmd, index, 2);
                        lst_addback(&root, set_correct_type(lst_new(ft_strdup(tmp)), 2));
                        track = 1;
                    }
                        free(tmp);
                }
                else
                {
                    tmp = ft_substr(cmd, index, 1);
                    lst_addback(&root, set_correct_type(lst_new(ft_strdup(tmp)), 1));
                    free(tmp);
                }
            }
            if (index != ft_strlen(cmd))
            {
                tmp = ft_strdup(cmd + index + 1 + track);
                free(cmd);
                cmd = ft_strdup(tmp);
                track = 0;
                index = -1;
                free(tmp);
            }
        }
        else if (db_sl_quote(cmd[index]))
        {
            if (index != 0)
            {
                tmp = ft_substr(cmd, 0, index);
                lst_addback(&root, set_correct_type(lst_new(ft_strdup(tmp)), 1));
                free(tmp);
                tmp = ft_substr(cmd ,index, ft_strlen(cmd + index));
                free(cmd);
                cmd = ft_strdup(tmp);
                free(tmp);
            }
            cmd = get_quotes(&root, cmd, index);
            if (!cmd)
                return (NULL);
            index = -1;
        }
    }
    printlist(root, 0);
    return(root);
}

//ls && (ls) ls handle cmd after subshell
// ls && >>f
//>_:hello"test"yy'tt' world

t_list *repair_list(t_list *root)
{
    t_list *new_list;
    t_list *holder;
    int track;
    int pth_track;
    
    pth_track = 0;
    track = 1;
    holder = root;
    new_list = NULL;
    while (root)
    {
        if (root->typeofcontent & token_pth)
        {
            if (lst_last(new_list) && (lst_last(new_list)->typeofcontent & token_pth \
                || (root->typeofcontent & token_par_in && !(lst_last(new_list)->typeofcontent & (token_pipe | token_and_or)))))
                return (printf("syntax error near \'%s'\n", root->content),NULL);
            lst_addback(&new_list, duplicate_node(root));
            if (root->typeofcontent & token_par_in)
                pth_track++;
            else if (root->typeofcontent & token_par_out)
                pth_track--;
        }
        else if (root->typeofcontent & token_meta)
        {
            if (new_list && root->typeofcontent & token_red && lst_last(new_list)->typeofcontent & token_and_or)
                ;
            else if ((new_list && lst_last(new_list)->typeofcontent & (token_red | token_and_or)) \
                || new_list && lst_last(new_list)->typeofcontent & token_pipe \
                && root->typeofcontent & token_pipe || !root->next \
                || (!new_list && root->typeofcontent & (token_pipe | token_and_or)))
                return (printf("Syntax error near %s\n", root->content), NULL);
            lst_addback(&new_list, duplicate_node(root));
            if (!track)
                track = 1;
        }
        else if (root->typeofcontent & (token_word | token_quote))
        {
            if (lst_last(new_list) && lst_last(new_list)->typeofcontent & token_par_out)
                return (printf("Syntax error near \'%s'\n", root->content), NULL);
            if (track || lst_last(new_list)->typeofcontent & token_meta)
                lst_addback(&new_list, duplicate_node(root));
            else
                lst_add_down(&new_list, duplicate_node(root));
            track = 0;
        }
        else if (root->typeofcontent & token_space)
            track = 1;
        root = root->next;
    }
    if (pth_track != 0)
        return (NULL);
    lst_clear(&holder);
    printlist(new_list, 1);
    return (new_list);
}

void *parsing(char *input)
{
    char *cmd;
    t_list *saved_list;
    t_list *cleared_list;
    t_btree *rootoftree;

    if (!input[0])
        return (NULL);
    cmd = ft_strdup(input);
    saved_list = tokenize_lex(cmd);
    if (!saved_list)
        return (free(cmd), NULL);
    free(cmd);
    lst_clear(&saved_list);
    return (1);
    // cleared_list = repair_list(saved_list); 
    // if (!cleared_list)
    //     return (lst_clear(saved_list), NULL);
    // lst_clear(&cleared_list);
    // printlist(saved_list, 1);
    // rootoftree = parse_ampersand_or(&saved_list);
    // if (!rootoftree)
    //     return (NULL);
    // print_tree(rootoftree);
    // return (rootoftree);
}
 // syntax error should be exit_status 258
int main (int ac, char *av[], char **env)
{
    static unsigned short status_code;
    char *input;
    char *keep;
    t_btree *exec_tree;
    t_listt *root_env;
    (void)av;
    
    if (ac != 1)
        return (printf("error arguments\n"), 0);
    root_env = create_envs(env);
    while (1)
    {
        input = NULL;
        input = readline(">_:");
        if (!input)
            return (printf("exit\n"));
        keep = ft_strtrim(input, " ");
        if (keep[0] != '\0' && keep)
        {
            exec_tree = (t_btree *)parsing(keep);
            if (!exec_tree && input[0] != '\0')
                (printf("Parsing Error\n"), status_code = 258); 
        }
        add_history(input);
        free(keep);
        free(input);
        // executing(exec_tree, root_env);
        // while (wait(0) != -1);
    }
}
    
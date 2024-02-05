/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:55:02 by ymabsout          #+#    #+#             */
/*   Updated: 2024/02/05 13:50:19 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// work with the double pointer to build the tree later , but the double pointer should be perfect before building the tree
#include "m1.h"

void printcmd(char **cmd)
{
    int i=-1;
    while (cmd[++i])
        printf("((%s))\n", cmd[i]);
}

// void *inputfix(char *s, char **cmd, int index)
// {

// }
void *trimcmd(char **cmd)
{
    int i;

    i = -1;
    while (cmd[++i])
        cmd[i] = ft_strtrim(cmd[i], " ");
    return (cmd);
}

// void *noinput(char *s, char **cmd)
// {
//     int i;

//     i = -1;
//     while (s[++i])
//     {
        
//     }
// }

void *fillcmd(char **cmd, int size, char *s) 
{
    int i;
    int id;
    int j;
// when there is input redirection, we will open the latest file displayed before a pipe or redirection 
 // in this commands : // cat < makefile main.c | grep e | wc -l, main.c will be opened and read from , use strrchr to search for space if there are any
 //if not then open the whole char *, JUST in case there is a command before redirection.
    (void)size;
    j = 0;
    id = -1;
    i = -1;
    while (s[++i])
    {
        if (id == -1 && s[i] == '<')
        {
            cmd[++id] = ft_strtrim(ft_substr(s, 0, i), " ");
            s = ft_substr(s, i, ft_strlen(s));
            printf("11%s11\n", s);
            i = -1;
        }
        else if (s[i] == '<')
        {
            cmd[++id] = ft_substr(s, i, i + 1);
            cmd[id] = ft_strtrim(cmd[id], " ");
            s = ft_strdup(s + i + 1);
            // while (s[++i] && s[i] == ' ')
            //     ;
            // while (s[++i] && s[i] != ' ')
            //     ;   
            // cmd[++id] = ft_substr(s, 0, i);
            // s = ft_strdup(s + i);
            i = -1;
        }
         if (s[i] == '|')
        {

            cmd[++id] = ft_substr(s, 0, i);
            cmd[++id] = ft_substr(s, i, 1);
            s = ft_strdup(s + i + 1);
            i = -1;
        }
        else if (s[i] == '>')
        {
            if (cmd[id][0] == '>' || cmd[id][0] == '<')
                return(printf("redirection error\n"), NULL);
            if (s[i + 1] == '>')
            {
                cmd[++id] = ft_substr(s, 0, i);
                cmd[++id] = ft_substr(s, i, 2);
                s = ft_substr(s, i + 2, ft_strlen(s));
            }
            else
            {
                cmd[++id] = ft_substr(s, 0, i);
                cmd[++id] = ft_substr(s, i, 1);
                s = ft_strdup(s + i + 1);
            }
            i = -1;
        }
    }
    // cmd[++id] = ft_strdup(s); //need to find a way to parse the last argument in  the command.
    // printf("00%s00\n", s);
    if (!ft_strncmp(cmd[id], " ", ft_strlen(cmd[id])) && id != 0)
        return(printf("Redirection invalid\n"), NULL);
    cmd[++id] = NULL;
    trimcmd(cmd);
    printcmd(cmd);
    return (cmd);
}

int skipspace(char *s)
{
    int index;

    index = 0;
    printf("%c\n", s[index]);
    while (s[index])
    {
        printf("%c\n", s[index]);
        if (s[index] == ' ')
            index ++;
        else
            return(index);
    }
    return(index);
}

void *remove_inner_space(char *s)
{
    int index;
    char *holder;
    int start;

    index = 0;
    holder = NULL;
    while (s[index])
    {
        while (s[index] && s[index] != ' ')
            index++;
        holder = ft_strjoin(holder, ft_substr(s, 0, index));
        printf("holder value 1: %s\n", holder);
        holder = ft_strjoin(holder ,ft_substr(s, index, 1));
        printf("holder value 2: %s>>>\n", holder);
        start = skipspace(s);
        printf("%d\n", start);
        s = ft_substr(s, start, ft_strlen(s));
        printf(" testing :%s\n", s);
        printf("holder value :%s\n", holder);
        index = 0;
    }
    return (holder);
}

void *tokenize(char *src)
{
    int i;
    t_list *root;

    i = 0;
    // printf("before trimming : %s\n", src);
    src = remove_inner_space(src);
    printf("after trimming : %s\n", src);
    // return NULL;
    // while (src[i])
    // {
    //     while (src[i] != ' ')
    //         i++;
    // lst_addback(root, lst_new(ft_substr(src, 0, i)));
    // lst_addback(root, lst_new(ft_substr(src, i, i + 1)));
    // src = ft_substr(src , i, i + 1);
    // }
}


void *token(char *str)
{
    int i;
    int keep;

    if (!tokenize(str))
        return (NULL);
    // if (!checkcmds(cmd, str, keep))
    //     return (NULL);
    return (str);
}

void *parsing(char *input , char **env)
{
    char *cmd;

    (void)env;
    cmd = ft_strdup(input);
    cmd = ft_strtrim(cmd, " ");
    if (!token(cmd))
        return (NULL);
    return (input);
}

int main (int ac, char *av[], char **env)
{
    if (ac != 1)
        return (printf("error arguments\n"), 0);
    (void)av;
    char *input = readline("Minishell:");
    while (input)
    {
        if (!parsing(input, env))
            printf("Parsing Error\n");
        add_history(input);
        input = readline("Minishell:");
    }
}
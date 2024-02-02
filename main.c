/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:55:02 by ymabsout          #+#    #+#             */
/*   Updated: 2024/02/02 21:31:36 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "m1.h"

void printcmd(char **cmd)
{
    int i=-1;
    while (cmd[++i])
        printf("*%s*\n", cmd[i]);
}


void *fillcmd(char **cmd, int size, char *s)
{
    int i;
    int id;

    (void)size;
    id = -1;
    i = -1;
    while (s[++i])
    {
        if (s[i] == '<')
        {
            cmd[++id] = ft_substr(s, 0, 1);
            s = ft_strdup(s + i + 1);
            while (s[++i] && s[i] == ' ')
                ;
            while (s[i] && s[++i] != ' ')
                ;
            cmd[++id] = ft_substr(s, 0, i);
            s = ft_strdup(s + i);
            i = -1;
        }
        else if (s[i] == '|')
        {
            cmd[++id] = ft_substr(s, 0, i);
            cmd[++id] = ft_substr(s, i, 1);
            s = ft_strdup(s + i + 1);
            i = -1;
        }
        else if (s[i] == '>')
        {
            if (!cmd[id] && (cmd[id][0] == '>' || cmd[id][0] == '<'))
                return(printf("redirection error\n"), NULL);
            if (s[i + 1] == '>')
            {
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
    cmd[++id] = ft_strdup(s);
    if (!ft_strncmp(cmd[id], "", ft_strlen(cmd[id])) && id != 0)
        return(printf("Redirection invalid\n"), NULL);
    cmd[++id] = NULL;
    printcmd(cmd);
    return (cmd);
}

void *token(char *str)
{
    int i;
    int count;
    char **cmd;
    int keep;
    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == '|' || str[i] == '<' || str[i] == '>')
            count++;
        i++;
    }
    keep = count;
    count += count +1;
    cmd = malloc((sizeof(char *) * count ) + 1);
    if (!cmd || !fillcmd(cmd, count, str))
        return (NULL);
    if (!checkcmds(cmd, str, keep))
        return (NULL);
    return (str);
}

void *parsing(char *input , char **env)
{
    char *cmd;
    int i;
    (void)env;
    i = 0;
    cmd = ft_strdup(input);
    if (!token(input))
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
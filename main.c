#include "m1.h"

void *fillcmd(char **cmd, int size, char *s)
{
    int i;
    int id;

    id = -1;
    i = -1;
    while (s[++i])
    {
        // printf("((%s))\n", s);
        if (s[i] == '|' || s[i] == '<' || s[i] == '>')
        {
            cmd[++id] = ft_substr(s, 0, i);
            cmd[++id] = ft_substr(s, i, 1);
            s = ft_strdup(s + i + 1);
            i = -1;
        }
    }
    cmd[++id] = ft_strdup(s);
    cmd[++id] = NULL;
    id = -1;
    while (cmd[++id])
        printf("(%s)\n", cmd[id]);
    return (cmd);
}


void *token(char *str)
{
    int i;
    int count;
    char **cmd;
    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == '|' || str[i] == '<' || str[i] == '>')
            count++;
        i++;
    }
    count += count +1;
    cmd = malloc((sizeof(char *) * count ) + 1);
    if (!cmd)
        return (NULL);
    fillcmd(cmd, count, str);
    return (str);
}


void *parsing(char *input , char **env)
{
    char *cmd;
    int i;
    int ind;

    i = 0;
    cmd = ft_strdup(input);
    if (!token(input))
        return (NULL);
    return (input);
}

int main (int ac, char *av[], char **env)
{
    char *input = readline("Minishell:");
    while (input)
    {
        if (!parsing(input, env))
            printf("Parsing Error\n");
        add_history(input);
        input = readline("Minishell:");
    }
}
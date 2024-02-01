#include "m1.h"

void parsing(char *input , char **env)
{
    char *cmd;
    int i;
    int ind;

    i = 0;
    cmd = ft_strdup(input);
    while(input[i])
    {
        if (ft_strchr(input, '|'))
        {
            printf("%s\n",input);
        }
    }
}

int main (int ac, char *av[], char **env)
{
    char *input = readline("Minishell:");
    while (input)
    {
        parsing(input, env);
        add_history(input);
        input = readline("Minishell:");
    }
}
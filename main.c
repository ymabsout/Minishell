/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:18:58 by smoumni           #+#    #+#             */
/*   Updated: 2024/02/13 17:42:45 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void del(void *cv)
{
    free((char *)cv);
}

void lol()
{
    system("leaks minishell");
}

int main(int argc, char **argv, char **env)
{
    t_list *root;
    
    root = create_envs(env);
    // char *ar[] = {"export", , NULL};
    // export_built_in(ar, &root);
    // char *arf[]= {"unset", "PWD", NULL};
    // unset_built_in(arf, &root);
    // char *arf[]= {"exit", "593", NULL};
    // exit_built_in(arf, 1);
    // char *arf[]= {"cd", "built_ins/", NULL};
    // cd_built_in(arf, &root);
    // char *arff[]= {"cd", "lol/", NULL};
    // cd_built_in(arff, &root);
    // printf("%s\n", getcwd(0, 0));
    // chdir(".");
    // printf("%s\n", getcwd(0, 0));
    // char *arff[]= {"env", "-i", NULL};
    // env_built_in(arff, root);
    printf("lol\n");
    while (root)
    {
        printf("%s\n", (char *)(root->content));
        root = root->next;
    }
    // char *arff[]= {"pwd", NULL};
    // pwd_built_in(arff);
}
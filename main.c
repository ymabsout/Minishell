/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:30:20 by ymabsout          #+#    #+#             */
/*   Updated: 2024/03/06 02:30:15 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

//ls && (ls) ls handle cmd after subshell
// ls && >>f
//>_:hello"test"yy'tt' world

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
        return (NULL);
    cleared_list = repair_list(saved_list);
    if (!cleared_list)
        return (lst_clear(&saved_list), NULL);
    lst_clear(&saved_list);
    saved_list = cleared_list;
    rootoftree = parse_ampersand_or(&cleared_list);
    if (!rootoftree)
        return (lst_clear(&cleared_list), NULL);
    // print_tree(rootoftree);
    lst_clear (&saved_list);
    return (rootoftree);
}

void get_here_doc(t_btree *exec_tree, int status, t_listt *env)
{
    if (!exec_tree)
        return ;
    get_here_doc(exec_tree->left, status, env);
    if (exec_tree->typeofcontent & token_red_here_doc)
        read_stdin(exec_tree, status, env);
    get_here_doc(exec_tree->right, status , env);
}

 // syntax error should be exit_status 258
int main (int ac, char *av[], char **env)
{
    char *input;
    char *keep;
    t_btree *exec_tree;
    t_listt *root_env;
    s_lol s;
    (void)av;

    if (ac != 1)
        return (printf("error arguments\n"), 0);
    root_env = create_envs(env);
    s.status_code = 0;
    input = NULL;   
    while (1)
    {
        handle_signal();
        input = readline(">_: ");
        if (received_signal == 2)
            (received_signal = 0, s.status_code = 1);
        if (!input)
            return (printf("exit\n"), s.status_code);
        keep = ft_strtrim(input, " ");
        if (keep && keep[0])
        {
            exec_tree = (t_btree *)parsing(keep);
            if (!exec_tree && input[0] != '\0')
                (printf("Parsing Error\n"), s.status_code = 258);
            if (exec_tree)
            {
                get_here_doc(exec_tree, s.status_code, root_env);
                print_tree(exec_tree);
                return_def();
                executing(exec_tree, root_env, &s);
                sig_def();
                if (waitpid(s.pids, &s.status_code, 0) != -1)
                {
                    if (WIFSIGNALED(s.status_code))
                    {
                        s.status_code = WTERMSIG(s.status_code) + 128;
                        if (s.status_code == 131)
                            printf("Quit: %d\n", WTERMSIG(s.status_code));
                        else if (s.status_code == 130)
                            printf("\n");
                    }
                    else
                        s.status_code = WEXITSTATUS(s.status_code);
                }
                while (waitpid(-1, 0, 0) != -1)
                    ;
                // printf("StatusCode: [%d]\n", s.status_code);
            }
            // Handle cat | cat | ls last child waiting on him!
        }
        add_history(input);
        free(input);
        free(keep);
    }
}
/// $(pwd)

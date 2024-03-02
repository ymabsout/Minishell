
#include "../mini_shell.h"

// void execute_left_cmd(t_btree *exec_tree, t_listt *env)
// {
//     char *cmd_path;
//     exec_tree->string = ft_joinAllNexts(exec_tree);

//     cmd_path = get_path_cmd(exec_tree->string[0], env);
//     // printf("[%s]\n", exec_tree->string[0]);
//     dup2(1, exec_tree->stdout);
//     printf("[%d]\n", exec_tree->stdout);
//     close(exec_tree->stdout);
//     close(exec_tree->stdin);
//     execve(cmd_path, exec_tree->string, 0);
// }


void redirect_streams(t_btree *node)
{ 
    if (node->stdout == 0)
        node->stdout = 1;
    if (node->stderr == 0)
        node->stderr = 2;
}

void executing(t_btree *exec_tree, t_listt *env)
{
    redirect_streams(exec_tree);

    if (exec_tree->typeofcontent & token_ampersand)
        execute_and_op(exec_tree, env);
    else if (exec_tree->typeofcontent & token_or)
        execute_or_op(exec_tree, env);
    else if (exec_tree->typeofcontent & token_pipe)
        execute_pipe(exec_tree, env);
    else if (exec_tree->typeofcontent & token_red_input)
        execute_red_input(exec_tree, env);
    else if (exec_tree->typeofcontent & token_red_out_trunc)
        execute_red_output(exec_tree, env, 1);
    else if (exec_tree->typeofcontent & token_red_out_append)
        execute_red_output(exec_tree, env, 0);
    else if (exec_tree->typeofcontent & token_word)
        execute_cmd(exec_tree, env);
}
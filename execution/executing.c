
#include "../mini_shell.h"

void redirect_streams(t_btree *node)
{ 
    if (node->stdout == 0)
        node->stdout = 1;
    if (node->stderr == 0)
        node->stderr = 2;
}

void  executing(t_btree *exec_tree, t_listt *env, s_lol *s)
{
    redirect_streams(exec_tree);

    if (exec_tree->flag_subshell)
        execute_sub_shell(exec_tree, env, s);
    else if (exec_tree->typeofcontent & token_ampersand)
        execute_and_op(exec_tree, env, s);
    else if (exec_tree->typeofcontent & token_or)
        execute_or_op(exec_tree, env, s);
    else if (exec_tree->typeofcontent & token_heredoc_append)
        execute_heredoc(exec_tree, env, s);
    else if (exec_tree->typeofcontent & token_pipe)
        execute_pipe(exec_tree, env, s);
    else if (exec_tree->typeofcontent & token_red_input)
        execute_red_input(exec_tree, env, s);
    else if (exec_tree->typeofcontent & token_red_out_trunc)
        execute_red_output(exec_tree, env, s, 1);
    else if (exec_tree->typeofcontent & token_red_out_append)
        execute_red_output(exec_tree, env, s, 0);
    else if (exec_tree->typeofcontent & (token_word | token_single_q | token_double_q))
        execute_cmd(exec_tree, env, s);
}
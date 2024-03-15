
#include "../../mini_shell.h"

static int check_wild_validation(t_btree *downs)
{
    int valid;

    valid = 0;
    while (downs)
    {
        if (find_num_char(downs->item, '*'))
        {
            valid = 1;
            if (find_num_char(downs->item, '\'') || \
                find_num_char(downs->item, '\"'))
                return (0);
        }
        downs = downs->down;
    }
    return (valid);
}

static t_btree *add_ls(t_btree *exec_tree, t_btree *data)
{
    t_btree *last;
    t_btree *buf;

    last = exec_tree->next;
    free(exec_tree->item);
    exec_tree->item = data->item;
    exec_tree->next = data->next;
    buf = data;
    while (data->next)
        data = data->next;
    free(buf);
    data->next = last;
    return (last);
}

void handle_wild(t_btree *exec_tree, int status_code, t_listt *env)
{
    t_btree *data;
    int is_valid;

    while (exec_tree)
    {
        data = 0;
        exec_tree->item = ft_joinAllDowns(&exec_tree, status_code, env);
        is_valid = check_wild_validation(exec_tree);
        if (is_valid)
            data = check_wild_card(exec_tree->item);
        if (data)
            exec_tree = add_ls(exec_tree, data);
        else
            exec_tree = exec_tree->next;
    }
}
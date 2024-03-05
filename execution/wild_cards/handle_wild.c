
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
            if (find_num_char(downs->item, '\'') || find_num_char(downs->item, '\"'))
                return (0);
        }
        downs = downs->down;
    }
    return (valid);
}

void handle_wild(t_btree *exec_tree, int status_code, t_listt *env)
{
    t_btree *data;
    t_btree *last;
    int is_valid;

    while (exec_tree)
    {
        data = 0;
        is_valid = check_wild_validation(exec_tree);
        exec_tree->item = ft_joinAllDowns(exec_tree, status_code, env);
        if (is_valid)
            data = check_wild_card(exec_tree->item);
        if (data)
        {
            last = exec_tree->next; // U need to free the first node;
            exec_tree->item = data->item;
            exec_tree->next = data->next;
            while (data->next)
                data = data->next;
            data->next = last;
            exec_tree = last;
        }
        else
            exec_tree = exec_tree->next;
    }
}
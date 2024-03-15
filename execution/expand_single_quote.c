#include "../mini_shell.h"

void expand_single_quote(t_btree *exec_tree)
{
    char *buffer;

    buffer = ft_strtrim(exec_tree->item, "\'");
    free(exec_tree->item);
    exec_tree->item = buffer;
}
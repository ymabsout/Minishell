
#include "../mini_shell.h"

void free_tree(t_btree *tree)
{
    if (!tree)
        return ;

    free_tree(tree->left);
    free_tree(tree->right);
    free_tree(tree->next);
    free_tree(tree->down);

    free_double(tree->string);
    free(tree->item);
    free(tree);
} 
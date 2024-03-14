#include "mini_shell.h"

void printdownlist(t_list *root)
{
    while (root)
    {
        printf("^^^^^down level ->{%s} --> type :{%d}^^^^\n", root->content, root->type);
        root = root->down;
    }
}

void printlist(t_list *root, int a)
{
    if (a == 1)
    {
        while (root)
        {
            printf("{%s} --> type :{%d}\n",  root->content, root->type);
            if (root->down)
                printdownlist(root->down);
            root = root->next;
        }
    }
    while (root)
    {
        printf("{%s} --> type :{%d}\n",  root->content, root->type);
        root = root->next;
    }
}

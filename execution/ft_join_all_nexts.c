
#include "../mini_shell.h"

static int ft_size(t_btree *tree)
{
    int i;

    i = 0;
    while (tree)
    {
        i++;
        tree = tree->next;
    }
    return (i);
}

static void free_nexts(t_btree *exec_tree)
{
    t_btree *next;

    while (exec_tree->next)
    {
        next = exec_tree->next;
        printf("not: %s\n", exec_tree->item);
        free(exec_tree->item);
        free(exec_tree);
        exec_tree = NULL;
        exec_tree = next;
    }
    free(exec_tree->item);
    free(exec_tree);
    next = NULL;
}

char **ft_join_all_nexts(t_btree *exec_tree, int status_code, t_listt *env)
{
    t_btree *curr;
    char **cmd;
    int next_size;
    int i;

    handle_wild(exec_tree, status_code, env);
    curr = exec_tree;
    next_size = ft_size(exec_tree);
    cmd = (char **)malloc((sizeof(char *) * (next_size)));
    if (!cmd)
        return (NULL);
    i = -1;
    while (++i < next_size)
    {
        cmd[i] = malloc(ft_strlen(exec_tree->item) + 1);
        if (!cmd[i])
            return (free_half_double(cmd, i), NULL);
        cmd[i] = ft_strdup(exec_tree->item);
        exec_tree = exec_tree->next;
    }
    cmd[i] = NULL;
    exec_tree = curr;
    free_nexts(curr);
    free_double(cmd);
    while(1);
    puts("Test");
    while (1);
    return (cmd);
}

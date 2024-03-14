#include "../../mini_shell.h"

static void setting_streams_out(t_btree *exec_tree, \
    int above_st, int target, int fd)
{
	if (target != 1)
    	exec_tree->stdout = target;
	else
    	exec_tree->stdout = fd;
    exec_tree->stdin = above_st;
}
static void setting_streams_in(t_btree *exec_tree, \
    int above_st, int target, int fd)
{
	if (target != 0)
    	exec_tree->stdin = target;
	else
    	exec_tree->stdin = fd;
    exec_tree->stdout = above_st;
}

static void dbl_setter(t_btree *exec_tree, char **string)
{
    int i;
    char **arr;

    i = -1;
    while (string[++i]) ;

    arr = malloc(sizeof(char *) * (i));
    if (!arr)
        return ;
    
    i = -1;
    while (string[(++i) + 1])
    {
        arr[i] = ft_strdup(string[i + 1]);
        if (!arr[i])
            return (free_half_double(arr, i));
    }
    arr[i] = NULL;
    exec_tree->string = arr;
    free_double(string);
}

static void cmd_on_right(t_btree *exec_tree, t_listt **env,  s_lol *s, int flag)
{
    int fd;

    fd = open_file(exec_tree->right, flag, s->status_code, env);
    if (fd < 0)
        return (fd_failure(exec_tree->right->string[0], fd, s));
    if (exec_tree->pipe_write_end && exec_tree->pipe_read_end)
    {
        exec_tree->right->pipe_write_end = exec_tree->pipe_write_end;
        exec_tree->right->pipe_read_end = exec_tree->pipe_read_end;
    }
    dbl_setter(exec_tree->right, exec_tree->right->string);
    if (flag >= 2)
        setting_streams_in(exec_tree->right, \
            exec_tree->stdout, exec_tree->stdin, fd);
    else
        setting_streams_out(exec_tree->right, \
            exec_tree->stdin, exec_tree->stdout, fd);
    executing(exec_tree->right, env, s);
    close(fd);
    (flag == 3 && unlink(exec_tree->right->item));
}
static int fn1(t_listt *l, int flag, s_lol *s, t_listt **env)
{
    int fd;
    t_listt *c;

    flag = 0;
    c = l;
    while (c)
    {
        if (((t_btree *)(c->content))->type & token_red_input)
            fd = open_file(((t_btree *)(c->content))->right, 2, s->status_code, env);
        else if (((t_btree *)(c->content))->type & token_red_out_trunc)
            fd = open_file(((t_btree *)(c->content))->right, 1, s->status_code, env);
        else if (((t_btree *)(c->content))->type & token_red_out_append)
            fd = open_file(((t_btree *)(c->content))->right, 0, s->status_code, env);
        if (fd < 0)
        {
            return (fd_failure(((t_btree *)(c->content))->right->string[0], fd, s), 1);
        }
        else
        {
            close(fd);
        }
        c = c->next;
    }
    c = l; 
    while (c)
    {
        if (((t_btree *)(c->content))->type & token_red_out_trunc)
            unlink(((t_btree *)(c->content))->right->string[0]);
        free_double(((t_btree *)(c->content))->right->string);
        ((t_btree *)(c->content))->right->string = 0;
        c = c->next;
    }
    return (0);
}

static int fn(t_btree *exec_tree, int flag, s_lol *s, t_listt **env)
{
    t_btree *curr;
    t_listt *l;

    l = 0;
    ft_lstadd_front(&l, ft_lstnew(exec_tree));
    curr = exec_tree->left;
    while (curr && curr->type & token_red)
    {
        ft_lstadd_front(&l, ft_lstnew(curr));
        curr = curr->left;
    }
    return (fn1(l, flag, s, env));
}

void execute_red(t_btree *exec_tree, t_listt **env, s_lol *s, int flag)
{
    int fd;
    char *file;
    static int i;

    if (exec_tree->left == NULL)
        return (cmd_on_right(exec_tree, env, s, flag));
    if (!i)
    {
        i = -1;
        if (fn(exec_tree, flag, s, env))
        {
            i = 0;
            return ;
        }
    }
    fd = open_file(exec_tree->right, flag, s->status_code, env);
    if (fd < 0)
        return (fd_failure(exec_tree->right->string[0], fd, s));
    if (exec_tree->pipe_write_end && exec_tree->pipe_read_end)
    {
        exec_tree->left->pipe_write_end = exec_tree->pipe_write_end;
        exec_tree->left->pipe_read_end = exec_tree->pipe_read_end;
    }
    file = exec_tree->right->string[0];
    free(file);
    exec_tree->left->string = ft_join_all_nexts(exec_tree->left, \
        s->status_code, env);
    create_string(exec_tree->left, exec_tree->right->string + 1);
    (free(exec_tree->right->string), exec_tree->right->string = NULL);
    if (flag >= 2)
        setting_streams_in(exec_tree->left, exec_tree->stdout, exec_tree->stdin, fd);
    else
        setting_streams_out(exec_tree->left, exec_tree->stdin, exec_tree->stdout, fd);
    (executing(exec_tree->left, env, s), close(fd));
    (flag == 3 && unlink(exec_tree->right->item));
}

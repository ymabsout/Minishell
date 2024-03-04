
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

static void expand_single_quote(t_btree *exec_tree)
{
    char *buffer;

    buffer = ft_strtrim(exec_tree->item, "\'");
    free(exec_tree->item);
    exec_tree->item = buffer;
}

static char *fn(char *complete_str, char *str, int del)
{
    int i;
    char *env;
    char *s;
    char *j;


    i = 0;
    while (++i)
        if (!ft_isalnum(str[i]) && str[i] != '_')
            break ;
    s = ft_substr(complete_str, 0, del);
    env = ft_substr(str, 1, i - 1);
    printf("(%s)\n", env);
    env = getenv(env);
    j = ft_strjoin(s, env);
    return (ft_strjoin(j, &str[i]));
}

static char *fn1(char *complete_str, char *str, int del, int status_code)
{
    char *s;
    char *j;
    char *code;

    s = ft_substr(complete_str, 0, del);
    code = ft_itoa(status_code);
    j = ft_strjoin(s, code);
    return (ft_strjoin(j, str + 2));
}

static void expand_dollar_sign(t_btree *exec_tree, int status_code)
{
    int i;

    i = -1;
    while (exec_tree->item[++i])
    {
        if (exec_tree->item[i] == '$')
        {
            if (ft_isalnum(exec_tree->item[i + 1]) || exec_tree->item[i + 1] == '_')
                exec_tree->item = fn(exec_tree->item, exec_tree->item + i, i);
            else if (exec_tree->item[i + 1] == '?')
                exec_tree->item = fn1(exec_tree->item, exec_tree->item + i, i, status_code);
        }
    }
}

static void expand_double_quote(t_btree *exec_tree, int status_code)
{
    char *buffer;

    buffer = ft_strtrim(exec_tree->item, "\"");
    free(exec_tree->item);
    exec_tree->item = buffer;
    expand_dollar_sign(exec_tree, status_code);

}

static char *ft_joinAllDowns(t_btree *exec_tree, int status_code)
{
    char *str;
    char *old_str;
    t_btree *down;

    if (exec_tree->typeofcontent & token_single_q)
        expand_single_quote(exec_tree);
    else
        expand_double_quote(exec_tree, status_code);
    str = exec_tree->item;
    exec_tree = exec_tree->down;
    while (exec_tree)
    {
        old_str = str;
        if (exec_tree->typeofcontent & token_single_q)
            expand_single_quote(exec_tree);
        else
            expand_double_quote(exec_tree, status_code);
        str = ft_strjoin(old_str, exec_tree->item);
        if (!str)
            return (free(old_str), NULL);
        free(old_str);
        down = exec_tree->down;
        free(exec_tree->item);
        free(exec_tree);
        exec_tree = down;
    }
    return (str);
}

static void free_nexts(t_btree *exec_tree)
{
    t_btree *next;

    while (exec_tree)
    {
        next = exec_tree->next;
        free(exec_tree->item);
        free(exec_tree);
        exec_tree = next;
    }
}

char **ft_join_all_nexts(t_btree *exec_tree, int status_code)
{
    t_btree *curr;
    char **cmd;
    int next_size;
    int i;

    handle_wild(exec_tree, status_code);
    next_size = ft_size(exec_tree);
    cmd = (char **)malloc((sizeof(char *) * (next_size + 1)));
    if (!cmd)
        return (NULL);
    curr = exec_tree;
    i = -1;
    while (++i < next_size)
    {
        cmd[i] = malloc(ft_strlen(curr->item) + 1);
        if (!cmd[i])
            return (free_double(cmd), NULL);
        cmd[i] = ft_strdup(curr->item);
        curr = curr->next;
    }
    free_nexts(exec_tree->next);
    cmd[i] = NULL;
    return (cmd);
}




//echo *.md
// echo built*
// echo oi*
// echo *.supp
// echo 'bye *' bo*s bye
// echo 'bye *' mini* bye
// echo *ME*
// echo "*"
// "*"
// manual*
// echo * | awk -v RS=" " '{print}' | sort
// <*.txt
// echo 'bye *' t*.c bye
// echo *EMPTY hello READ* world
// cat <README*
// echo "pip*"
// echo *bonus *.supp bonjour
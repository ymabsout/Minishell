#include <stdio.h>
#include <stdlib.h>
t_btree *create_node(void *content);

enum(
    TOKEN_PIPE;
    TOKEN_PIPELINE,
    TOKEN_RED
);
typedef struct s_tree {
    void *content;
    struct s_tree *left;
    struct s_tree *right;
    int type;
} t_btree;

t_btree *create_node(void *content) {
    t_btree *node = malloc(sizeof(t_btree));
    if (!node)
        return NULL;
    memset(node, 0, sizeof(t_btree));
    node->content = content;
    return (node);
}

t_btree *get_root(char **s)
{
    t_btree *tmp = get_red(s);
    t_btree * tmp1;

}

t_btree *get_red(char **s)
{
    t_btree *tmp = get_pipe_line(s);
    t_btree * tmp1;
}

t_btree *get_pipe_line(char **s)
{
    char *tmp;
    int i =-1;
    while(*s[++i] != ' ')
        ;
    tmp = ft_substr
}

int main ()
{
    t_btree * root;
    char *s = "ls | grep";
    root = get_root(&s);

}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_tree {
    void *content;
    struct s_tree *left;
    struct s_tree *right;
    int type;
} t_btree;

enum{
    TOKEN_ADD,
    TOKEN_MULT,
    TOKEN_NUMBER,
    TOKEN_DIVIDE,
    TOKEN_MINUS
};

t_btree *parse_sum(char **s);
t_btree *parse_fac(char **s);
t_btree *parse_divide(char **s);

t_btree *create_node(void *content) {
    t_btree *node = malloc(sizeof(t_btree));
    if (!node)
        return NULL;
    memset(node, 0, sizeof(t_btree));
    node->content = content;
    return (node);
}

t_btree *parse_sum(char **s) {
    t_btree *tmp = parse_divide(s);
    t_btree *fact;
    char c;
    while (**s == ' ')
        (*s)++;
    while (**s == '+' || **s == '-') {
        c = **s;
        (*s)++;
        t_btree *tmp1 = parse_divide(s);
        if (c == '+')
        {
            fact = create_node("+");
            fact->type = TOKEN_ADD;// set the correct token for the node
        }
        else 
        {
            fact = create_node("-");
            fact->type = TOKEN_MINUS;// set the correct token for the node
        }
        fact->left = tmp;
        fact->right = tmp1;
        tmp = fact;
    }
    return (tmp);
}

t_btree *parse_divide(char **s) {
    t_btree *node = parse_fac(s);
    t_btree *fact;
    char c;
    while (**s == ' ')
        (*s)++;
    while (**s == '/' || **s == '*') {
        c = **s;
        (*s)++;
        t_btree *tmp1 = parse_fac(s);
        t_btree *tmp2 = node;
        if (c == '/')
        {
            fact = create_node("/");
            fact->type = TOKEN_DIVIDE; // set the correct token for the node
        }
        else 
        {
            fact = create_node("*");
            fact->type = TOKEN_MULT;
        }
        fact->left = tmp2;
        fact->right = tmp1;
        node = fact;
    }
    return (node);
}

t_btree *parse_fac(char **s) {
    char *a= malloc(sizeof(char )+ 1);
    char c;
    t_btree *node;
    while (**s == ' ')
        (*s)++;
    if (**s >= '0' && **s <= '9') {
        a[0]= **s;
        a[1]= '\0';
        node = create_node(a);
        node->type = TOKEN_NUMBER;
        (*s)++;
        return (node); // Pass the dynamically allocated integer to the node, with the specified token ":number"
    }
    if (**s == '(') {
        (*s)++;
        t_btree *tmp = parse_sum(s);
        (*s)++;
        return (tmp);
    } else {
        fprintf(stderr, "Expected number or '(' got %c\n", **s);
        exit(EXIT_FAILURE);
    }
}

void print_tree(t_btree *root) {
    if (!root)
        return ;
    printf("%s\n", (char *)root->content);
    print_tree(root->left);
    printf("^^^%s^^^\n", (char *)root->content);
    print_tree(root->right);
}

int main() {
    char *s = "2*(7+3)+8-7-2*4"; 
    char *s1 = "2*(5/5)"; 
    t_btree *root = parse_sum(&s);

    print_tree(root);
    return 0;
}

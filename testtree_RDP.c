#include "m1.h"

t_btree *parse_sum(t_list **root) {
    t_btree *tmp = parse_divide(root);
    t_btree *fact;
    t_list *holder;
    int tokn_type;

    holder = *root;
    while (holder->typeofcontent & token_and_or) 
    {
        tokn_type = holder->typeofcontent;
        (*root) = (*root)->next;
        t_btree *tmp1 = parse_divide(root);
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

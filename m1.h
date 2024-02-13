#ifndef M1_H
# define M1_H

typedef struct s_tree {
    char  *item;
    struct s_tree *left;
    struct s_tree *right;
    int type;
} t_btree;

typedef struct s_list
{
    char *content;
    int typeofcontent;
    char **joined_content;
    struct s_list *next;
    struct s_list *previous;
    struct s_list *up;
    struct s_list *down;
}   t_list;


# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <termios.h>

enum token_type
{
    token_ampersand = 1 << 0,
    token_or = 1 << 1,
    token_red_out_trunc = 1 << 2,
    token_red_out_append = 1 << 3,
    token_red_here_doc = 1 << 4,
    token_red_input = 1 << 5,
    token_pipe = 1 << 6,
    token_word = 1 << 7,
    token_double_q = 1 << 8,
    token_single_q = 1 << 9,
    token_space = 1 << 10,
    token_red = (token_red_out_trunc | token_red_out_append | token_red_here_doc | token_red_input),
    token_meta = (token_pipe | token_red),
    token_quote = (token_double_q | token_single_q),
    token_and_or = (token_ampersand | token_or)
};

typedef struct s_conv
{
    int i;
	int red;
	char **meta;
	char **com;
    char *s;
	int j;
	int k;
    t_btree *root;
}   t_cms; //content management system


t_btree *btree_create_node(void *item);
char	**ft_split(char const *s, char c);
void	fill(char *arr, char **s, char c);
char	**freearr(int index, char **arr);
int     count_words(char *s, char c);
int     len_world(char *s, char c);
char	*ft_strdup(char *s);
int	ft_strlen(const char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strchr(char *s, int c);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strrchr(char *s, int c);
int     ft_strncmp(char *s1, char *s2, size_t n);
void    *checkcmds(char **cmd, char *str, int count);
void    splitcmds(t_cms *infs, char **cmd);
void    btree_insert_data(t_btree **root, void *item);
void    lst_addback(t_list **root, t_list *node);
t_list  *lst_new(char *content);
char	*ft_strjoin(char *s1, char *s2);
void    *parsing(char *input);
void    *tokenize_lex(char *cmd);
t_list  *duplicate_node(t_list *root);
void    deletenode(t_list *holder, t_list *node_delete);
t_list *lst_last(t_list *root);
void	lst_add_down(t_list **lst, t_list *new);
void	*ft_memset(void *s, int c, size_t n);


#endif 
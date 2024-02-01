#ifndef M1_H
# define M1_H

typedef struct s_btree
{
    struct s_btree *left;
    struct s_btree *right;
    void *item;
}   t_btree;

typedef struct s_list
{
    void *content;
    struct s_list *next;
}   t_list;

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
}   t_cms;


# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <termios.h>

t_btree *btree_create_node(void *item);
char	**ft_split(char const *s, char c);
void	fill(char *arr, char **s, char c);
char	**freearr(int index, char **arr);
int     count_words(char *s, char c);
int     len_world(char *s, char c);
char	*ft_strdup(char *s);
size_t	ft_strlen(const char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strchr(char *s, int c);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strrchr(char *s, int c);
int     ft_strncmp(char *s1, char *s2, size_t n);
void    *checkcmds(char **cmd, char *str, int count);
void    splitcmds(t_cms *infs, char **cmd);
void btree_insert_data(t_btree **root, void *item);


#endif 
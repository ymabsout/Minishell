

#ifndef MINI_SHELL_H
#define MINI_SHELL_H

#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <termios.h>
#include <dirent.h>
#include <signal.h>

#define PATH "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."

typedef struct s_list
{
    char *content;
    int typeofcontent;
    char **joined_content;
    struct s_list *next;
    struct s_list *previous;
    struct s_list *up;
    struct s_list *down;
} t_list;

typedef struct s_tree
{
    struct s_tree *left;
    struct s_tree *right;
    int typeofcontent;
    char **string;
    int flag_subshell;
    struct s_tree *next;
    struct s_tree *down;
    char *item;

    // PIPE
    int pipe_read_end;
    int pipe_write_end;

    //
    int ln;
    int rn;

    //
    int stdin;
    int stdout;
    int stderr;

    //
} t_btree;

typedef struct s_listt
{
    struct s_listt *next;
    void *content;
} t_listt;

typedef struct t_lol {
    int status_code;
    pid_t pids;
} s_lol;

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
    token_par_in = 1 << 11,
    token_par_out = 1 << 12,
    token_heredoc_append = (token_red_out_append | token_red_here_doc),
    token_red = (token_red_out_trunc | token_heredoc_append | token_red_input),
    token_quote = (token_double_q | token_single_q),
    token_and_or = (token_ampersand | token_or),
    token_af_pipe = (token_pipe | token_and_or),
    token_meta = (token_pipe | token_red | token_and_or),
    token_pth = (token_par_in | token_par_out)
};

char *ft_strchr(char *s, int c);
char *ft_strrchr(char *s, int c);
void lst_addback(t_list **lst, t_list *new);
t_list *lst_new(char *content);
void *parsing(char *input);
void *tokenize_lex(char *cmd);
t_list *duplicate_node(t_list *root);
void deletenode(t_list *holder, t_list *node_delete);
t_list *lst_last(t_list *root);
void lst_add_down(t_list **lst, t_list *new);
void *ft_memset(void *s, int c, size_t n);
void print_tree(t_btree *root);
t_btree *parse_cmd(t_list **root);
t_btree *duplicate_for_tree(t_list *root);
t_btree *parse_pipe(t_list **root);
t_btree *parse_heredoc_append(t_list **root);
t_btree *parse_ampersand_or(t_list **root);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char *get_next_line(int fd);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strdup(const char *s1);
int ft_strncmp(const char *s1, const char *s2, size_t n);
size_t ft_strlen(const char *s);
void ft_putstr_fd(char *s, int fd);
size_t ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);
char *ft_itoa(int n);
int ft_isalnum(int c);
void ft_lstadd_back(t_listt **lst, t_listt *new);
void ft_lstadd_front(t_listt **lst, t_listt *new);
void ft_lstclear(t_listt **lst, void (*del)(void *));
void ft_lstdelone(t_listt *lst, void (*del)(void *));
void ft_lstiter(t_listt *lst, void (*f)(void *));
t_listt *ft_lstlast(t_listt *lst);
t_listt *ft_lstmap(t_listt *lst, void *(*f)(void *), void (*del)(void *));
t_listt *ft_lstnew(void *content);
int ft_lstsize(t_listt *lst);
char **ft_split(char const *s, char c);
int ft_isalpha(int c);
int ft_atoi(const char *str);
char	*ft_strtrim(char const *s1, char const *set);

void syntax_error(void);
void err_handler(int num);

char *expand_env_vars(char *str, int state_code);
void handle_unclosed_quotes(char *line, int *state);
int find_num_char(char *str, int c);
void free_double(char **arr);
void valid_id_error(char *cmd, char *id);

t_listt *create_envs(char **env);

// BUILT-INS
int export_built_in(char **cmd, t_listt **head_env);
int env_built_in(char **cmd, t_listt *head_env);
int unset_built_in(char **cmd, t_listt **head_env);
int exit_built_in(char **cmd, int status_code);
int pwd_built_in(char **cmd);
int echo_built_in(char **cmd);
int cd_built_in(char **cmd, t_listt **head_env);
int env_built_in(char **cmd, t_listt *head_env);

// Error
void failing_err(int failed);

// CODE
void executing(t_btree *exec_tree, t_listt *env, s_lol *s);
void handle_cmd_not_found(char *cmd);
t_btree *check_wild_card(char *str);

// EXECUTION
void execute_or_op(t_btree *exec_tree, t_listt *env,  s_lol *s);
void execute_and_op(t_btree *exec_tree, t_listt *env,  s_lol *s);
void execute_pipe(t_btree *exec_tree, t_listt *env,  s_lol *s);
void execute_left_cmd(t_btree *exec_tree, t_listt *env);
void execute_right_cmd(t_btree *exec_tree, t_listt *env);
void execute_solo_cmd(t_btree *exec_tree, t_listt *env);
void execute_cmd(t_btree *exec_tree, t_listt *env,  s_lol *s);
void execute_red_input(t_btree *exec_tree, t_listt *env,  s_lol *s);
void execute_red_output(t_btree *exec_tree, t_listt *env,  s_lol *s, int flag);
void execute_sub_shell(t_btree *exec_tree, t_listt *env, s_lol *s);
void execute_heredoc(t_btree *exec_tree, t_listt *env, s_lol *s);
int execute_built_in(t_btree *exec_tree, t_listt *env, s_lol *s);
char *get_path_cmd(char *cmd, t_listt *env);
char **ft_join_all_nexts(t_btree *exec_tree, int status_code, t_listt *env);
char *ft_joinAllDowns(t_btree *exec_tree, int status_code, t_listt *env);
void print_down_tree(t_btree *root);

// Wild card
void handle_wild(t_btree *exec_tree, int status_code, t_listt *env);
t_btree *check_wild_card(char *str);
char *match(char *file_name, char *pattern);

void expand_single_quote(t_btree *exec_tree);
void expand_double_quote(t_btree *exec_tree, int status_code, t_listt *env);


t_btree *lst_last_tree(t_btree *root);

#endif
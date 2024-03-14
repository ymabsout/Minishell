/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:50:00 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/14 22:06:47 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <termios.h>
# include <dirent.h>
# include <signal.h>
# define PATH "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."

int	g_received_signal;

typedef struct s_list
{
	char			*content;
	int				typeofcontent;
	char			**joined_content;
	struct s_list	*next;
	struct s_list	*previous;
	struct s_list	*up;
	struct s_list	*down;
}	t_list;

typedef struct s_tree
{
	struct s_tree	*left;
	struct s_tree	*right;
	int				typeofcontent;
	char			**string;
	int				flag_subshell;
	struct s_tree	*next;
	struct s_tree	*down;
	char			*item;
	int				pipe_read_end;
	int				pipe_write_end;
	int				stdin;
	int				stdout;
	int				stderr;
}	t_btree;

typedef struct s_listt
{
	struct s_listt	*next;
	void			*content;
}	t_listt;

typedef struct s_quote
{
	int	dbl;
	int	sgl;
}	t_data_q;

typedef struct s_util
{
	int		status_code;
	pid_t	pid;
}	t_util;

enum e_token_type
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
	token_pth = (token_par_in | token_par_out),
	token_parse = (token_word | token_quote | token_red | token_pth)
};

void	lst_addback(t_list **lst, t_list *new);
t_list	*lst_new(char *content);
void	*parsing(char *input);
void	*tokenize_lex(char *cmd);
t_list	*duplicate_node(t_list *root);
void	deletenode(t_list *holder, t_list *node_delete);
t_list	*lst_last(t_list *root);
void	lst_add_down(t_list **lst, t_list *new);
void	print_tree(t_btree *root);
t_btree	*parse_cmd(t_list **root);
t_btree	*duplicate_for_tree(t_list *root);
t_btree	*parse_pipe(t_list **root);
t_btree	*parse_heredoc_append(t_list **root);
t_btree	*parse_ampersand_or(t_list **root);

void	*ft_memset(void *s, int c, size_t n);
char	*ft_strchr(char *s, int c);
char	*ft_strrchr(char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, int start, int len);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, int n);
int		ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlcat(char *dst, const char *src, int dstsize);
size_t	ft_strlcpy(char *dst, const char *src, int dstsize);
char	*ft_itoa(int n);
int		ft_isalnum(int c);
void	ft_lstadd_back(t_listt **lst, t_listt *new);
void	ft_lstadd_front(t_listt **lst, t_listt *new);
void	ft_lstclear(t_listt **lst, void (*del)(void *));
void	ft_lstdelone(t_listt *lst, void (*del)(void *));
t_listt	*ft_lstnew(void *content);
int		ft_lstsize(t_listt *lst);
char	**ft_split(char const *s, char c);
int		ft_isalpha(int c);
int		ft_atoi(const char *str);
char	*ft_strtrim(char const *s1, char const *set);

void	export_no_args(t_listt *head_env);
int		check_args_export(char *cmd, int *is_plus);
void	export_plus(t_listt **head_env, char *env_var);
void	replace_env(t_listt *node, char *env_var);
void	add_env(t_listt **head_env, char *env_var);
void	export(t_listt **head_env, char *env_var);
int		export_built_in(char **cmd, t_listt **head_env);
int		env_built_in(char **cmd, t_listt *head_env);
int		unset_built_in(char **cmd, t_listt **head_env);
int		exit_built_in(char **cmd, int status_code);
int		pwd_built_in(char **cmd);
int		echo_built_in(char **cmd);
int		cd_built_in(char **cmd, t_listt **head_env);

void	fd_failure(char *file, int id, t_util *s);
int		sys_failing(int err, char *fn, t_util *s);
void	handle_cmd_not_found(char *cmd);
void	valid_id_error(char *cmd, char *id);

void	executing(t_btree *exec_tree, t_listt *env, t_util *s);
void	execute_or_op(t_btree *exec_tree, t_listt *env, t_util *s);
void	execute_and_op(t_btree *exec_tree, t_listt *env, t_util *s);
void	execute_pipe(t_btree *exec_tree, t_listt *env, t_util *s);
void	execute_cmd(t_btree *exec_tree, t_listt *env, t_util *s);
void	execute_sub_shell(t_btree *exec_tree, t_listt *env, t_util *s);
void	execute_heredoc(t_btree *exec_tree, t_listt *env, t_util *s);
int		execute_built_in(t_btree *exec_tree, t_listt *env, t_util *s);
char	*get_path_cmd(char *cmd, t_listt *env);
char	**ft_join_all_nexts(t_btree *exec_tree, int status_code, t_listt *env);
char	*ft_join_all_downs(t_btree *exec_tree, int status_code, t_listt *env);
void	expand_dollar_sign(t_btree *exec_tree, int status_code, t_listt *env);
void	print_down_tree(t_btree *root);
void	execute_red(t_btree *exec_tree, t_listt *env, t_util *s, int flag);
int		open_file(t_btree *exec_tree, int flag, int status_code, t_listt *env);
void	create_string(t_btree *exec_tree, char **string);
t_btree	*check_wild_card(char *str);
void	handle_wild(t_btree *exec_tree, int status_code, t_listt *env);
t_btree	*check_wild_card(char *str);
char	*match(char *file_name, char *pattern);
void	expand_single_quote(t_btree *exec_tree);
void	expand_double_quote(t_btree *exec_tree, int status_code, t_listt *env);

void	read_stdin(t_btree *exec_tree, int status_code, t_listt *env);
void	routine_heredoc(int fd, t_btree *exec_tree, \
	int status_code, t_listt *env);
void	*get_file(void);
char	*ft_join_alldowns_heredoc(t_btree *exec_tree);
void	expand_single_quote_heredoc(t_btree *exec_tree);
void	expand_double_quote_heredoc(t_btree *exec_tree);

void	print_next_tree(t_btree *root);
void	print_down_tree(t_btree *root);
void	print_tree(t_btree *root);
void	printdownlist(t_list *root);
void	printlist(t_list *root, int a);

void	heredoc_signal();
void	handle_signal();
void	return_def();
void	sig_def();
void	lst_addback(t_list **lst, t_list *new);

t_btree	*lst_last_tree(t_btree *root);
void	lst_clear(t_list **root);
int		delimeter(int c);
void	*set_correct_follow(t_list *root, int numb);
void	*set_correct_type(t_list *root, int numb);
int		db_sl_quote(int c);
void	*get_cmd_back(char *cmd, int index, t_list **root, int type);
void	*update_trackers(char *cmd, int index, t_data_q *track);
void	*get_quotes(t_list **root, char *cmd, int index);
t_list	*repair_list(t_list *root);
void	*parsing(char *input);
void	*dbl_sgl_handle(t_list **root, char *cmd, int *index);
void	*handle_delimeter(char *cmd, t_list **root, int *index, int *track);
void	*delim_follows(char *cmd, t_list **root, int *index, int *track);
void	*statement_delim(char *cmd, int *index, int *track, t_list **root);
void	*white_space_handle(char *cmd, int *index, t_list **root);
void	*type_parser(t_list **root, t_list **new_list, int *track, int *pth);
void	*meta_cmd_parser(t_list **root, t_list **new_list, int *track);
void	*cmd_parse(t_list **root, t_list **new_list, int *track);
void	handle_ctrl_c();

t_listt	*create_envs(char **env);
int		find_num_char(char *str, int c);
void	free_double(char **arr);
void	free_half_double(char **cmd, int i);
void	free_tree(t_btree *tree);

#endif
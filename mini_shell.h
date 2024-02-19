        /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:01:43 by smoumni           #+#    #+#             */
/*   Updated: 2024/02/05 18:34:35 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
#define MINI_SHELL_H

#define READLINE_TITLE "MiniShell> "

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/readline.h>

typedef struct s_list
{
    struct s_list *next;
    void *content;
} t_list;

void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_itoa(int n);
int	ft_isalnum(int c);
char	*ft_strdup(const char *s1);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int	ft_lstsize(t_list *lst);
char	**ft_split(char const *s, char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_isalpha(int c);
int	ft_atoi(const char *str);

void    syntax_error(void);
void    err_handler(int num);

char    *expand_env_vars(char *str, int state_code);
void handle_unclosed_quotes(char *line, int *state);
int find_num_char(char *str, int c);
void free_double(char **arr);
void valid_id_error(char *cmd, char *id);

t_list *create_envs(char **env);

// BUILT-INS
int export_built_in(char **cmd, t_list **head_env);
int env_built_in(char **cmd, t_list *head_env);
int unset_built_in(char **cmd, t_list **head_env);
int exit_built_in(char **cmd, int status_code);
int pwd_built_in(char **cmd);
int echo_built_in(char **cmd);
int cd_built_in(char **cmd, t_list **head_env);

#endif
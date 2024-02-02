/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:01:43 by smoumni           #+#    #+#             */
/*   Updated: 2024/02/02 19:32:31 by smoumni          ###   ########.fr       */
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

void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_itoa(int n);
int	ft_isalnum(int c);
char	*ft_strdup(const char *s1);

void    syntax_error(void);
void    err_handler(int num);

char    *expand_env_vars(char *str, int state_code);
void handle_unclosed_quotes(char *line, int *state);
int find_num_char(char *str, int c);


#endif
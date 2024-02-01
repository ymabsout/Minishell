#ifndef M1_H
# define M1_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <termios.h>

char	**ft_split(char const *s, char c);
void	fill(char *arr, char **s, char c);
char	**freearr(int index, char **arr);
int     count_words(char *s, char c);
int     len_world(char *s, char c);
char	*ft_strdup(const char *s, int length);
size_t	ft_strlen(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strchr(char *s, int c);

#endif 
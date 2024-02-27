/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:06:58 by smoumni           #+#    #+#             */
/*   Updated: 2024/02/26 23:34:41 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_new_line(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

static int	get_index_newline(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		i++;
	}
	return (i);
}

static char	*read_buffer(char *line, int fd, int *size)
{
	char	*arr;

	arr = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!arr)
	{
		if (line)
			free(line);
		return (line = NULL, NULL);
	}
	*size = read(fd, arr, BUFFER_SIZE);
	if (*size == -1)
	{
		if (line)
			free(line);
		return (free(arr), line = NULL, NULL);
	}
	arr[*size] = '\0';
	if (*size == 0)
		return (free(arr), line);
	line = ft_strjoinn(line, arr);
	free(arr);
	return (arr = NULL, line);
}

static char	*get_line(char **line)
{
	int		index;
	int		line_len;
	char	*one_line;
	char	*tmp;

	line_len = 0;
	while ((*line)[line_len])
		line_len++;
	index = get_index_newline(*line);
	if (index == line_len - 1)
	{
		one_line = ft_strdupp(*line);
		return (free(*line), *line = NULL, one_line);
	}
	one_line = ft_substrr(*line, 0, index + 1);
	tmp = ft_strdupp(*line + index + 1);
	free(*line);
	*line = tmp;
	return (tmp = NULL, one_line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*one_line;
	int			size;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (NULL);
	size = 1;
	while (size && !check_new_line(line))
	{
		line = read_buffer(line, fd, &size);
		if (!line)
			return (line = NULL, NULL);
	}
	if (size == 0 && !check_new_line(line))
	{
		one_line = ft_strdupp(line);
		return (free(line), line = NULL, one_line);
	}
	one_line = get_line(&line);
	return (one_line);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:42:23 by ymabsout          #+#    #+#             */
/*   Updated: 2024/02/12 15:36:11 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../m1.h"

char	**freearr(int index, char **arr)
{
	int	i;

	i = 0;
	while (i <= index)
	{
		free(arr[index]);
		index--;
	}
	free(arr);
	return (NULL);
}

int	count_words(char *s, char c)
{
	int	count;
	int	found;
	int	i;

	i = 0;
	count = 0;
	found = 1;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			if (found == 1)
			{
				found = 0;
				count++;
			}
		}
		if (s[i] == c)
			found = 1;
		i++;
	}
	return (count);
}

int	len_world(char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != '\0' && s[i] == c)
		i++;
	while (s[i] != '\0' && s[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

void	fill(char *arr, char **s, char c)
{
	int	i;

	i = 0;
	while (**s && **s == c)
		(*s)++;
	while (**s && **s != c)
	{
		arr[i] = **s;
		(*s)++;
		i++;
	}
	arr[i] = '\0';
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**arr;
	int		count;
	int		length;
	char	*s1;

	if (!s)
		return (NULL);
	i = 0;
	s1 = (char *)s;
	count = count_words(s1, c);
	arr = (char **)malloc(sizeof(char *) * (count_words(s1, c) + 1));
	if (!arr)
		return (NULL);
	while (i < count)
	{
		length = len_world(s1, c);
		arr[i] = (char *)malloc(sizeof(char) * length + 1);
		if (!arr[i])
			return (freearr(i, arr));
		fill(arr[i], &s1, c);
		i++;
	}
	arr[i] = 0;
	return (arr);
}

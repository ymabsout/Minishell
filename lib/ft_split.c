/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:09:45 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/13 17:44:31 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	count_words(const char *s, char c)
{
	int		count;
	int		i;
	int		found;

	count = 0;
	i = 0;
	found = 1;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (found == 1)
			{
				count++;
				found = 0;
			}
		}
		else
			found = 1;
		i++;
	}
	return (count);
}

static int	count_word_len(const char *s, char c)
{
	int		count;

	count = 0;
	while (*s == c)
		s++;
	while (*s && *s != c)
	{
		count++;
		s++;
	}
	return (count);
}

static void	insert_strings(char *arr, char const **s, char c)
{
	int		i;
	int		found;
	char	**s1;

	i = 0;
	found = 1;
	s1 = (char **)s;
	while (**s1)
	{
		if (**s1 != c)
		{
			arr[i] = **s1;
			found = 0;
			i++;
		}
		else
		{
			if (found == 0)
				break ;
			found = 1;
		}
		(*s1)++;
	}
	arr[i] = '\0';
}

static void	free_memory(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	int		i;
	char	**arr;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	arr = (char **)malloc((words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < words)
	{
		arr[i] = malloc(count_word_len(s, c) + 1 * sizeof(char));
		if (!arr[i])
		{
			free_memory(arr, i);
			return (NULL);
		}
		insert_strings(arr[i], &s, c);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

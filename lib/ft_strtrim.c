/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 03:21:47 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 03:22:25 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	find_start_index(char const *str, char const *set)
{
	int		start;
	int		i;

	start = 0;
	i = 0;
	while (set[i])
	{
		if (set[i] == str[start])
		{
			start++;
			i = 0;
		}
		else
			i++;
	}
	return (start);
}

static int	find_end_index(char const *str, char const *set)
{
	int		end;
	int		i;

	end = ft_strlen(str) - 1;
	i = 0;
	while (set[i] && end >= 0)
	{
		if (set[i] == str[end])
		{
			end--;
			i = 0;
		}
		else
			i++;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;

	if (!s1)
		return (NULL);
	if (!set || !set[0] || !s1[0])
		return (ft_strdup(s1));
	start = find_start_index(s1, set);
	end = find_end_index(s1, set);
	if (start > end)
		return (ft_strdup(""));
	return (ft_substr(s1, start, end - start + 1));
}

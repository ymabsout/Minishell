/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:41:43 by smoumni           #+#    #+#             */
/*   Updated: 2024/02/02 16:42:08 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static char	*handle_one_str_util(char const *s)
{
	char	*arr;
	size_t	s_len;

	s_len = ft_strlen(s);
	arr = (char *)malloc((s_len + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	ft_strlcpy(arr, s, (s_len + 1));
	return (arr);
}

static char	*handle_one_str(char const *s1, char const *s2)
{
	if (!s1)
		return (handle_one_str_util(s2));
	return (handle_one_str_util(s1));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*arr;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 || !s2)
		return (handle_one_str(s1, s2));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	arr = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	ft_strlcpy(arr, s1, (s1_len + s2_len + 1));
	ft_strlcat(arr, s2, (s1_len + s2_len + 1));
	return (arr);
}

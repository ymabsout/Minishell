/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:07:16 by smoumni           #+#    #+#             */
/*   Updated: 2024/02/26 23:34:19 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlenn(char *s)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdupp(char *s1)
{
	size_t	i;
	size_t	s1_len;
	char	*arr;

	s1_len = ft_strlenn(s1);
	arr = (char *)malloc((s1_len + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		arr[i] = s1[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

size_t	ft_strlcatt(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	i = 0;
	src_len = ft_strlenn(src);
	dst_len = ft_strlenn(dst);
	if (dst_len >= dstsize || dstsize == 0)
		return (dstsize + src_len);
	while (src[i] != '\0' && i < dstsize - dst_len - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

char	*ft_strjoinn(char *s1, char *s2)
{
	char	*arr;
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdupp(s2));
	if (!s2)
		return (ft_strdupp(s1));
	s1_len = ft_strlenn(s1);
	s2_len = ft_strlenn(s2);
	arr = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		arr[i] = s1[i];
		i++;
	}
	arr[i] = '\0';
	ft_strlcatt(arr, s2, (s1_len + s2_len + 1));
	return (free(s1), s1 = NULL, arr);
}

char	*ft_substrr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*arr;

	if (!s)
		return (NULL);
	if (start >= ft_strlenn(s))
		return (ft_strdupp(""));
	if (len + start > ft_strlenn(s))
		return (ft_strdupp(s + start));
	arr = (char *)malloc((len + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		arr[i] = s[start + i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:41:19 by ymabsout          #+#    #+#             */
/*   Updated: 2024/03/14 22:22:27 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"


char	*ft_strchr(char *s, int c)
{
	int				i;
	unsigned char		*str;

	if (!s[0] && c == '\0')
		return ((char *)s);
	i = 0;
	str = (unsigned char *)s;
	while (i <= ft_strlen(s))
	{
		if (str[i] == (unsigned char)c)
			return ((char *)str + i);
		else
			i++;
	}
	return (NULL);
}

int	ft_memcmp(void *s1, void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}

char	*ft_strrchr(char *s, int c)
{
	unsigned char	*str;
	int				length_str;

	str = (unsigned char *)s;
	length_str = ft_strlen(s);
	while (length_str >= 0)
	{
		if (str[length_str] == (unsigned char)c)
			return ((char *)(str + length_str));
		length_str--;
	}
	return (NULL);
}

void dl(void *content)
{
	free((char *)content);
}

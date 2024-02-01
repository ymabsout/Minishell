/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:41:19 by ymabsout          #+#    #+#             */
/*   Updated: 2024/02/01 09:02:00 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m1.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	length_s;
	size_t	i;

	i = 0;
	length_s = ft_strlen(s);
	ptr = (char *)malloc((length_s * sizeof(char)) + 1);
	if (ptr == NULL)
		return (NULL);
	while (i <= length_s && s[i] != '\0')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length])
	{
		length++;
	}
	return (length);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	ptr = malloc(sizeof(char) * len + 1);
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	size_t				i;
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
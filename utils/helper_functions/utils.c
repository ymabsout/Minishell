/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:41:19 by ymabsout          #+#    #+#             */
/*   Updated: 2024/03/03 00:34:47 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"


// char	*ft_strdup(char *s)
// {
// 	char	*ptr;
// 	size_t	length_s;
// 	size_t	i;

// 	i = 0;
// 	length_s = ft_strlen(s);
// 	ptr = (char *)malloc((length_s * sizeof(char)) + 1);
// 	if (ptr == NULL)
// 		return (NULL);
// 	while (i <= length_s && s[i] != '\0')
// 	{
// 		ptr[i] = s[i];
// 		i++;
// 	}
// 	ptr[i] = '\0';
// 	return (ptr);
// }

// char	*ft_substr(char *s, unsigned int start, size_t len)
// {
// 	char	*ptr;
// 	size_t	i;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	if (start > ft_strlen(s))
// 		return (ft_strdup(""));
// 	if (len > ft_strlen(s) - start)
// 		len = ft_strlen(s) - start;
// 	ptr = malloc(sizeof(char) * len + 1);
// 	if (ptr == NULL)
// 		return (NULL);
// 	while (i < len)
// 	{
// 		ptr[i] = s[start];
// 		i++;
// 		start++;
// 	}
// 	ptr[i] = '\0';
// 	return (ptr);
// }

char	*ft_strchr(char *s, int c)
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

// int	ft_strncmp(char *s1, char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!s1 || !s2)
// 		return (-1);
// 	while (i < n)
// 	{
// 		if ((unsigned char)s1[i] == (unsigned char)s2[i] && i < ft_strlen(s1))
// 			i++;
// 		else
// 		{
// 			if ((unsigned char)s1[i] > (unsigned char)s2[i])
// 				return (1);
// 			else if ((unsigned char)s1[i] < (unsigned char)s2[i])
// 				return (-1);
// 			else
// 				return (0);
// 		}
// 	}
// 	return (0);
// }

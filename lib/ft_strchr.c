/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:59:59 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 03:20:20 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*ft_strchr(char *s, int c)
{
	int				i;
	unsigned char	*str;

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

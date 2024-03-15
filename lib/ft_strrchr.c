/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:59:06 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/13 17:59:17 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

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

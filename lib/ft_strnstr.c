/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 03:21:39 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/15 03:21:46 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	y;

	if (!needle && !needle[0])
		return ((char *)haystack);
	if (!haystack && !haystack[0])
		return (NULL);
	i = 0;
	while (i < len && haystack[i])
	{
		y = 0;
		while (i + y < len && haystack[i + y] == needle[y])
		{
			if (needle[y + 1] == '\0')
				return ((char *)&(haystack[i]));
			y++;
		}
		i++;
	}
	return (NULL);
}

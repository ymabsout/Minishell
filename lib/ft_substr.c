/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:03:22 by smoumni           #+#    #+#             */
/*   Updated: 2024/02/02 16:48:57 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*arr;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len + start > ft_strlen(s))
		return (ft_strdup(s + start));
	arr = malloc((len + 1) * sizeof(char));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:52:18 by smoumni           #+#    #+#             */
/*   Updated: 2024/03/09 19:44:32 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	s1_len;
	char	*arr;

	if (!s1)
		return (0);
	s1_len = ft_strlen(s1);
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

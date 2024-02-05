/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymabsout <ymabsout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:19:16 by ymabsout          #+#    #+#             */
/*   Updated: 2024/02/05 13:34:24 by ymabsout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m1.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	if (!s2 && !s1)
		return (NULL);
	if (!s1)
		return(ft_strdup(s2));
	if (!s2)
		return(ft_strdup(s1));
	ptr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!ptr)
		return (NULL);
	i = -1;
	while (++i < ft_strlen(s1))
		ptr[i] = s1[i];
	j = 0;
	while (j < ft_strlen(s2))
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

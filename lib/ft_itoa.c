/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:40:29 by smoumni           #+#    #+#             */
/*   Updated: 2024/02/02 18:33:32 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static void	insert_digits(char **arr, int n)
{
	if (n < 0)
	{
		**arr = '-';
		(*arr)++;
		insert_digits(arr, -n);
	}
	else if (n > 9)
	{
		insert_digits(arr, n / 10);
		insert_digits(arr, n % 10);
	}
	else
	{
		**arr = n + '0';
		(*arr)++;
	}
}

static int	count_digits(int n)
{
	int		c;

	c = 0;
	if (n <= 0)
	{
		c++;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		c++;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	char	*arr;
	int		digits;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	digits = count_digits(n);
	arr = malloc((digits + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	insert_digits(&arr, n);
	*arr = '\0';
	return (arr - digits);
}

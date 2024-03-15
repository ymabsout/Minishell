/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:43:06 by smoumni           #+#    #+#             */
/*   Updated: 2024/02/01 13:26:04 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void    syntax_error(void)
{
    ft_putstr_fd("Syntax error unclosed quote\n", 2);
    exit(EXIT_FAILURE);
}
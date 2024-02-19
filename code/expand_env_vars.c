/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoumni <smoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:38:11 by smoumni           #+#    #+#             */
/*   Updated: 2024/02/02 19:07:58 by smoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static char *join_all(char *joinable, char *whole_str, int ind)
{
    char *first_part;
    char *perfect_str;

    first_part = ft_substr(whole_str, 0, ind);
    perfect_str = ft_strjoin(first_part, joinable);
    free(first_part);
    free(joinable);
    return (perfect_str);
}

static char *expanding(char *whole_str, char *str, int *ind)
{
    int index;
    int clone_ind;
    char *env_name;
    char *env_expanded;

    index = 0;
    while (str[++index])
    {
        if (!ft_isalnum(str[index]))
            break ;
    }
    env_name = ft_substr(str, 1, index - 1);
    env_expanded = getenv(env_name);
    free(env_name);
    clone_ind = *ind;
    if (env_expanded)
        *ind = ft_strlen(env_expanded) + *ind;
    return (join_all(ft_strjoin(env_expanded, &str[index]), whole_str, clone_ind));
}

static char *expanding_status_code(int status_code, char *whole_str, char *str, int *ind)
{
    char *status_str;
    char *expanded_str;
    int clone_ind;
    size_t len_str;

    status_str = ft_itoa(status_code);
    len_str = ft_strlen(status_str);
    clone_ind = *ind;
    *ind = len_str + *ind;
    expanded_str = ft_strjoin(status_str, &str[2]);
    free(status_str);
    return (join_all(expanded_str, whole_str, clone_ind));
}

char *expand_env_vars(char *str, int state_code)
{
    int index;
    char *clone;
    int single_quote_radar;

    index = -1;
    single_quote_radar = 0;
    while (str[++index])
    {
        if (str[index] == '\'')
            single_quote_radar++;
        if (single_quote_radar % 2 == 0 && str[index] == '$')
        {
            clone = str;
            if (str[index + 1] == '?')
                str = expanding_status_code(state_code, str, &str[index], &index);
            else
                str = expanding(str, &str[index], &index);
            free(clone);
        }
    }
    return (str);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_pront.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:41:46 by frivas            #+#    #+#             */
/*   Updated: 2025/03/25 15:44:19 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ms_get_host(char *str)
{
    char    *res;
    int     i;
    int     end;
    int     start;
    int     len;

    res = NULL;
    i = 0;
    end = 0;
    start = 0;
    while (str[i])
    {
        if (str[i] == '.')
        {
            end = i;
            break;
        }
        i++;
    }
    while(str[i] && i > 0)
    {
        if (str[i] == '/')
        {
            start = i + 1;
            break;
        }
        i--;
    }
    len = end - start;
    res = ft_substr(str, start, len);
    return (res);
}

void    ms_get_pront(t_mshell **data)
{
    char    *temp;
    char    *hostn;
    char    *pwdir;
    
    (void)  data;

    temp = getenv("SESSION_MANAGER");
    hostn = ms_get_host(temp);
    pwdir getenv()
    printf("%s\n", hostn);    
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_pront.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:41:46 by frivas            #+#    #+#             */
/*   Updated: 2025/03/25 16:26:36 by brivera          ###   ########.fr       */
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

char	*ms_get_dir(char *str)
{
}


void    ms_get_pront(t_mshell **data)
{
	char    *temp;
	char    *hostn;
	char    *pwdir;


	temp = getenv("SESSION_MANAGER");
	hostn = ms_get_host(temp);
	free(temp);
	pwdir = getenv("PWD");
	temp = ms_get_dir(temp);
	printf("%s\n", hostn);    
}

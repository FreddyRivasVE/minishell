/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_together.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:42:24 by frivas            #+#    #+#             */
/*   Updated: 2025/04/25 11:37:09 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_newlen_str(char *str)
{
	int		i;
	int		j;
	char	*res;
		
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i + 1] == '<' || str[i + 1] == '>')
				i++;
			if (ft_isspace(str[i + 1]))
				i++;
			else
				j++;
		}
		i++;
	}
	res = ft_calloc(ft_strlen(str) + j + 1, sizeof(char));
	if (!res)
		return (NULL);
	return (res);
}

char	*ms_redir_together(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = ms_newlen_str(str);
	while (str[i])
	{
		res[j] = str[i];
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i + 1] == '<' || str[i + 1] == '>')
				res[++j] = str[++i];
			if (ft_isspace(str[i + 1]))
				res[++j] = str[++i];
			else
				res[++j] = ' ';
		}
		i++;
		j++;
	}
	return (res);
}

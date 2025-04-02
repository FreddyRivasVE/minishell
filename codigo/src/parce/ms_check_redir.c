/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:40:59 by frivas            #+#    #+#             */
/*   Updated: 2025/04/02 16:38:00 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_check_redir(char *str)
{
	int 	i;
	bool	check_redir;

	i = 0;
	check_redir = false;

	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '<' || str[i] == '>')
	{
		i++;
		if(str[i] == '<' || str[i] == '>')
			i++;
		while (str[i])
		{
			if (ft_isascii(str[i]))
				check_redir = true;
			if (str[i] == '<' || str[i] == '>')
				check_redir = false;
			i++;
		}
	}
	return (check_redir);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:40:59 by frivas            #+#    #+#             */
/*   Updated: 2025/04/03 18:07:47 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// revisar si esta todo ok, encontre que habia cosas que aun no controlaba 
// creo que ahora si, pero bueno la dividimos cuando este todo ok 
// o si vemos que se puede hacer mas simple mejor 

#include "minishell.h"

bool	ms_check_redir(char *str)
{
	size_t	i;
	bool	check_redir;
	size_t	flag;

	check_redir = true;
	i = ft_strcspn(str, "<>");
	if (i < ft_strlen(str))
	{
		check_redir = false;
		flag = 1;
		i++;
	}
	while (str[i])
	{
		if ((str[i] == '<' || str[i] == '>'))
		{
			flag++;
			check_redir = false;
		}
		if (ft_isascii(str[i]) && (str[i] != '<' && str[i] != '>') && (flag < 3))
		{
			check_redir = true;
			flag = 0;
		}
		i++;
	}
	return (check_redir);
}

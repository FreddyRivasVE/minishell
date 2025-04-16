/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:40:59 by frivas            #+#    #+#             */
/*   Updated: 2025/04/16 15:56:25 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_redirection_char(char c)
{
	return (c == '<' || c == '>');
}

static bool	ms_redir_result(size_t i, size_t flag, bool check_redir, char *str)
{
	while (str[i])
	{
		if (is_redirection_char(str[i]))
		{
			flag++;
			check_redir = false;
		}
		if (ft_isascii(str[i]) && !is_redirection_char(str[i]) && (flag < 3))
		{
			check_redir = true;
			flag = 0;
		}
		i++;
	}
	return (check_redir);
}

bool	ms_check_redir(char *str)
{
	size_t	i;
	size_t	flag;
	bool	check_redir;

	flag = 0;
	check_redir = true;
	i = ft_strcspn(str, "<>");
	if (i < ft_strlen(str))
	{
		check_redir = false;
		flag = 1;
		i++;
	}
	return (ms_redir_result(i, flag, check_redir, str));
}

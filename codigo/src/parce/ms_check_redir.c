/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:40:59 by frivas            #+#    #+#             */
/*   Updated: 2025/04/29 15:14:25 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isredirection_char(char c)
{
	return (c == '<' || c == '>');
}

static int	ms_ignored_quotes(char *str, int i)
{
	bool	squote;
	bool	dquote;

	squote = false;
	dquote = false;
	squote = toggle_simples(str[i], squote, dquote);
	dquote = toggle_doubles(str[i], squote, dquote);
	if (squote || dquote)
	{
		i++;
		if (squote)
		{
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (dquote)
		{
			while (str[i] && str[i] != '\"')
				i++;
		}
	}
	return (i);
}

static bool	ms_redir_result(size_t flag, bool check_redir, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		i = ms_ignored_quotes(str, i);
		if (ft_isredirection_char(str[i]))
		{
			flag++;
			check_redir = false;
		}
		if (ft_isascii(str[i]) && !ft_isredirection_char(str[i]) && (flag < 3))
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
	size_t	flag;
	bool	check_redir;

	flag = 0;
	check_redir = true;
	if (ft_strchr(str, '<') || ft_strchr(str, '>'))
		check_redir = false;
	return (ms_redir_result(flag, check_redir, str));
}

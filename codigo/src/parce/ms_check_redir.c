/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:40:59 by frivas            #+#    #+#             */
/*   Updated: 2025/05/03 18:59:21 by brivera@stu      ###   ########.fr       */
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

static bool	ms_redir_result(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		i = ms_ignored_quotes(str, i);
		if (ft_isredirection_char(str[i]))
		{
			i++;
			if (i > 0 && str[i] == str[i - 1])
				i++;
			if (str[i] == '\0')
				return (false);
			while (str[i])
			{
				if (ft_isredirection_char (str[i]) || (str[i + 1] == '\0'))
					return (false);
				if (!ft_isspace(str[i]) && ft_isprint(str[i]))
					break ;
				i++;
			}
			i--;
		}
		i++;
	}
	return (true);
}

bool	ms_check_redir(char *str)
{
	size_t	flag;
	bool	check_redir;

	flag = 0;
	check_redir = true;
	if (ft_strchr(str, '<') || ft_strchr(str, '>'))
		check_redir = ms_redir_result(str);
	return (check_redir);
}

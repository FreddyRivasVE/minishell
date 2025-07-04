/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:40:59 by frivas            #+#    #+#             */
/*   Updated: 2025/06/02 08:35:48 by brivera          ###   ########.fr       */
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

static bool	check_after_redirection(char *str, int *i)
{
	(*i)++;
	if (*i > 0 && str[*i] == str[*i - 1])
		(*i)++;
	while (str[*i])
	{
		if (ft_isredirection_char(str[*i]))
			return (false);
		if (!ft_isredirection_char(str[*i])
			&& !ft_isspace(str[*i]) && ft_isprint(str[*i]))
			break ;
		(*i)++;
	}
	if (str[*i] == '\0')
		return (false);
	(*i)--;
	return (true);
}

static bool	ms_redir_result(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i = ms_ignored_quotes(str, i);
		if (ft_isredirection_char(str[i]))
		{
			if (!check_after_redirection(str, &i))
				return (false);
		}
		i++;
	}
	return (true);
}

bool	ms_check_redir(char *str)
{
	bool	check_redir;

	check_redir = true;
	if (ft_strchr(str, '<') || ft_strchr(str, '>'))
		check_redir = ms_redir_result(str);
	return (check_redir);
}

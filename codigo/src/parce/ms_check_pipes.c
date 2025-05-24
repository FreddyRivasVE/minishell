/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:49:24 by frivas            #+#    #+#             */
/*   Updated: 2025/05/22 17:52:48 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_pipe_position(char *str, int i, bool dquote, bool squote)
{
	int	j;

	if (str[i] != '|' || dquote || squote)
		return (true);
	j = i - 1;
	while (j >= 0 && ft_isspace(str[j]))
		j--;
	if (j >= 0 && ft_isredirection_char(str[j]))
		return (false);
	j = i + 1;
	while (str[j] && ft_isspace(str[j]))
		j++;
	if (str[j] == '\0')
		return (false);
	if (str[j] == '|')
		return (false);
	if (ft_isredirection_char(str[j]))
	{
		while (str[j] && ft_isspace(str[j]))
			j++;
		if (str[j] == '\0' || str[j] == '|'
			|| (ft_isredirection_char(str[j]) && str[j + 1] == '\0'))
			return (false);
	}
	return (true);
}

bool	ms_has_leading_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (str[i] == '|');
}

bool	ms_check_pipes(char *str)
{
	int		i;
	bool	squote;
	bool	dquote;

	if (ms_has_leading_pipe(str))
		return (false);
	i = 0;
	squote = false;
	dquote = false;
	while (str[i])
	{
		if (!dquote && str[i] == '\'')
			squote = !squote;
		if (!squote && str[i] == '\"')
			dquote = !dquote;
		if (!is_valid_pipe_position(str, i, dquote, squote))
			return (false);
		i++;
	}
	return (true);
}

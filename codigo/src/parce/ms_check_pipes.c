/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:49:24 by frivas            #+#    #+#             */
/*   Updated: 2025/05/03 18:53:12 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_pipe_position(char *str, int i, bool dquote, bool squote)
{
	int	j;

	if (str[i] != '|' || dquote || squote)
		return (true);
	j = i + 1;
	while (str[j] && ft_isspace(str[j]))
		j++;
	if (str[j] == '\0')
		return (false);
	if (str[j] == '|' || ft_isredirection_char(str[j]))
	{
		while (str[j] && ft_isspace(str[j]))
			j++;
		if (str[j] == '\0')
			return (false);
	}
	return (true);
}

static bool	has_leading_pipe(char *str)
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

	if (has_leading_pipe(str))
		return (false);
	i = 0;
	squote = false;
	dquote = false;
	while (str[i])
	{
		dquote = toggle_doubles(str[i], squote, dquote);
		squote = toggle_simples(str[i], squote, dquote);
		if (!is_valid_pipe_position(str, i, dquote, squote))
			return (false);
		i++;
	}
	return (true);
}

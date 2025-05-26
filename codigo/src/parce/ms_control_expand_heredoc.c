/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_control_expand_heredoc.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:29:32 by frivas            #+#    #+#             */
/*   Updated: 2025/05/26 17:15:12 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ms_heredoc_expand_aux(char *str, int pos, int i)
{
	int	j;
	int	k;

	j = i + 1;
	while (str[j] && ft_isspace(str[j]))
		j++;
	if (j <= pos)
	{
		k = j;
		while (k < pos && !ft_isspace(str[k]))
			k++;
		if (k >= pos)
			return (true);
	}
	return (false);
}

bool	ms_control_expand_hered(char *str, int pos, t_mshell *data)
{
	int		i;
	bool	heredoc;
	bool	dquote;

	i = pos;
	heredoc = false;
	dquote = data->flag;
	while (i >= 0)
	{
		if (i > 0 && str[i] == '<' && str[i - 1] == '<' && !dquote)
		{
			heredoc = true;
			break ;
		}
		if (str[i] == '\"')
			dquote = !dquote;
		i--;
	}
	if (heredoc)
		return (ms_heredoc_expand_aux(str, pos, i));
	return (false);
}

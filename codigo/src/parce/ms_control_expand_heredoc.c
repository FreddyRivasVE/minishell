/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_control_expand_heredoc.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:29:32 by frivas            #+#    #+#             */
/*   Updated: 2025/05/22 09:13:44 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_control_expand_hered(char *str, int pos, t_mshell *data)
{
	int		i;
	bool	dobleq;

	dobleq = data->flag;
	i = 0;
	if (pos > 0)
		i = pos - 1;
	if (!ft_isspace(str[i]))
	{
		while (i >= 0 && !ft_isspace(str[i]))
			i--;
	}
	while (i >= 0 && (ft_isspace(str[i]) || str[i] == '\"'))
	{
		if (str[i] == '\"' && dobleq)
			dobleq = false;
		else if (str[i] == '\"' && !dobleq)
			dobleq = true;
		i--;
	}
	if (i > 0 && str[i] == '<' && str[i - 1] == '<' && dobleq == 0)
		return (true);
	return (false);
}

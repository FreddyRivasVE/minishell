/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_control_expand_heredoc.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:29:32 by frivas            #+#    #+#             */
/*   Updated: 2025/05/20 23:33:53 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_control_expand_heredoc(char *str, int pos, t_mshell *data)
{
	int		i;
	bool	dobleq;

	dobleq = data->flag;
	i = pos - 1;
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


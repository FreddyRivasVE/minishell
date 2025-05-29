/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_redir_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-29 11:06:40 by brivera           #+#    #+#             */
/*   Updated: 2025-05-29 11:06:40 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_run_isspace(char *str, int i)
{
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

bool	ms_has_redir_at_start(char *str)
{
	int	i;

	i = 0;
	i = ms_run_isspace(str, i);
	if (str[i] != '\0' && ft_isredirection_char(str[i]) && str[i + 1] == '\0')
		return (true);
	if (str[i] != '\0' && ft_isredirection_char(str[i])
		&& !ft_isredirection_char(str[i + 1]))
	{
		i = ms_run_isspace(str, i);
		if (str[i] == '\0' || ft_isredirection_char(str[i]))
		{
			if (str[i] != '\0' && ft_isredirection_char(str[i])
				&& !ft_isredirection_char(str[i + 1]))
			{
				i++;
				i = ms_run_isspace(str, i);
				if (str[i] == '\0' || ft_isredirection_char(str[i]))
					return (true);
			}
			if (str[i] == '\0')
				return (true);
		}
	}
	return (false);
}

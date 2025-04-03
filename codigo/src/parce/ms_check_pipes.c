/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:49:24 by frivas            #+#    #+#             */
/*   Updated: 2025/04/03 18:05:38 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_check_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '|')
		return (false);
	while (str[i])
	{
		if (str[i] == '|')
			if (str[i + 1] == '|' || (str[i + 1] == '<' || str[i + 1] == '>'))
				return (false);
		i++;
	}
	while (!str[i] || str[i] == ' ')
		i--;
	if (str[i] == '|')
		return (false);
	return (true);
}

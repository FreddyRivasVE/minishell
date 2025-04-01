/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_quotation_marks.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:37:27 by frivas            #+#    #+#             */
/*   Updated: 2025/04/02 00:18:29 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_check_quotation_marks(char *str)
{
	bool	check_simples;
	bool	check_doubles;
	int		i;

	check_simples = false;
	check_doubles = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			check_simples ^= true;
		else if (str[i] == '\"')
			check_doubles ^= true;
		i++;
	}
	if (check_simples || check_doubles)
		return (true);
	return (false);
}

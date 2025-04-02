/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_quotation_marks.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:37:27 by frivas            #+#    #+#             */
/*   Updated: 2025/04/02 13:26:52 by brivera          ###   ########.fr       */
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
		{
			if(check_doubles == true)
			{
				if(check_simples == true)
					check_simples ^= false;
			}
			else
				check_simples ^= true;
		}
		else if (str[i] == '\"')
		{
			if(check_simples == true)
			{	
				if(check_doubles == true)
					check_doubles ^= false;
			}
			else
				check_doubles ^= true;
		}
		i++;
	}
	if (check_simples || check_doubles)
		return (false);
	return (true);
}

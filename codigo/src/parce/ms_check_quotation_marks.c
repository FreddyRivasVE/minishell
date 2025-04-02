/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_quotation_marks.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:37:27 by frivas            #+#    #+#             */
/*   Updated: 2025/04/03 01:16:26 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	toggle_simples(char c, bool check_simples, bool check_doubles)
{
	if (c == '\'')
	{
		if (check_doubles)
		{
			if (check_simples)
				check_simples ^= false;
		}
		else
			check_simples ^= true;
	}
	return (check_simples);
}

bool	toggle_doubles(char c, bool check_simples, bool check_doubles)
{
	if (c == '\"')
	{
		if (check_simples)
		{
			if (check_doubles)
				check_doubles ^= false;
		}
		else
			check_doubles ^= true;
	}
	return (check_doubles);
}

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
		check_simples = toggle_simples(str[i], check_simples, check_doubles);
		check_doubles = toggle_doubles(str[i], check_doubles, check_simples);
		i++;
	}
	if (check_simples || check_doubles)
		return (false);
	return (true);
}

/*bool	ms_check_quotation_marks(char *str)
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
			if (check_doubles == true)
			{
				if (check_simples == true)
					check_simples ^= false;
			}
			else
				check_simples ^= true;
		}
		else if (str[i] == '\"')
		{
			if (check_simples == true)
			{
				if (check_doubles == true)
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
}*/

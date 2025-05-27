/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:40:04 by frivas            #+#    #+#             */
/*   Updated: 2025/05/27 13:03:34 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_is_n_flag(char *str)
{
	int	i;

	if (str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ms_echo(char **command)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (command[i] && ms_is_n_flag(command[i]))
	{
		newline = 0;
		i++;
	}
	while (command[i])
	{
		ft_putstr_fd(command[i], 1);
		if (command[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_orquest_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:57:44 by frivas            #+#    #+#             */
/*   Updated: 2025/04/29 19:18:41 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_reserve_mm_command(t_mshell *data, char ***split, char **tag)
{
	int	i;
	int	j;
	int	k;
	int	commands;

	i = 0;
	k = 0;
	commands = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (!ft_strcmp(tag[k], "COMMAND"))
				commands++;
			j++;
			k++;
		}
		data->commands[i].command = ft_calloc(commands + 1, sizeof(char *));
		if (!data->commands[i].command)
			return (-1);
		i++;
	}
	return (0);
}


int	ms_orquest_command(t_mshell *data, char ***split, char **tag)
{
	int	i;
	int	j;
	int	k;
	int	l;

	if (ms_reserve_mm_command(data, split, tag) == -1)
		return (-1);
	i = 0;
	k = 0;
	while (split[i])
	{
		j = 0;
		l = 0;
		while (split[i][j])
		{
			if (!ft_strcmp(tag[k], "COMMAND"))
			{
				data->commands[i].command[l] = ft_strdup(split[i][j]);
				l++;
			}
			j++;
			k++;
		}
		i++;
	}
	return (0);
}

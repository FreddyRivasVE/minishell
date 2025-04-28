/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pre_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:34:03 by frivas            #+#    #+#             */
/*   Updated: 2025/04/28 11:56:34 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_num_commands(t_mshell *data)
{
	int			i;
	int			j;
	char		***inputs;
	int			ncommand;

	ncommand = 0;
	inputs = data->inputs->splitaftpipes;
	i = 0;
	while (inputs[i])
	{
		j = 0;
		while (inputs[i][j])
		{
			if (inputs[i][j][0] == '<' || inputs[i][j][0] == '>')
				j = j + 2;
			else
			{
				ncommand++;
				j++;
			}
		}
		i++;
	}
	return (ncommand);
}

void	ms_pre_commands(t_mshell *data)
{
	int		i;
	int		j;
	int		k;
	char	***inputs;

	data->commands->command = ft_calloc(ms_num_commands(data) + 1, sizeof(char *));
	if (!data->commands->command)
		return ;
	inputs = data->inputs->splitaftpipes;
	i = 0;
	while (inputs[i])
	{
		j = 0;
		k = 0;
		while (inputs[i][j])
		{
			if (inputs[i][j][0] == '<' || inputs[i][j][0] == '>')
				j = j + 2;
			else
			{
				data->commands->command[k] = ft_strdup(inputs[i][j]);
				j++;
				k++;
			}
		}
		i++;
	}
}

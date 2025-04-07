/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:46:39 by frivas            #+#    #+#             */
/*   Updated: 2025/04/07 23:28:50 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***ms_split_postpipe(t_mshell *data)
{
	char	***commands;
	int		i;
	char	**temp;

	i = 0;
	temp = data->inputs->splitpipes;
	while (temp[i])
		i++;
	commands = malloc(sizeof(char **) * (i + 1));
	if (!commands)
		return (NULL);
	i = 0;	
	while (temp[i])
	{
		commands[i] = ft_split(temp[i], ' ');
		i++;
	}
	commands[i] = NULL;
	return (commands);	
}


int	ms_split_input(t_mshell *data)
{
	data->inputs = malloc(sizeof(t_input));
	if (!data->inputs)
		return (0);
	data->inputs->splitpipes = ft_split(data->input_row, '|');
	//ft_print_array(data->inputs->splitpipes); // Borrar mas adelante.
	data->inputs->splitaftpipes = ms_split_postpipe(data);
	free_array(data->inputs->splitpipes);
	return (1);
}



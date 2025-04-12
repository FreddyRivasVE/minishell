/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:46:39 by frivas            #+#    #+#             */
/*   Updated: 2025/04/12 18:31:22 by frivas           ###   ########.fr       */
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
		commands[i] = ft_split_quotes(temp[i]);
		if (!commands[i])
			return (free_triple_array(commands), NULL);
		i++;
	}
	commands[i] = NULL;
	return (commands);
}

int	ms_split_input(t_mshell *data)
{
	int	exit;

	data->inputs = malloc(sizeof(t_input));
	if (!data->inputs)
		return (0); 
	data->inputs->splitpipes = ft_split_pipes(data->input_row);
	if (!data->inputs->splitpipes)
		return (0);
	//ft_print_array(data->inputs->splitpipes); // Borrar mas adelante.
	data->inputs->splitaftpipes = ms_split_postpipe(data);
	ft_print_array_triple(data->inputs->splitaftpipes); // Borrar mas adelante.
	exit = ms_expand_variable(data);
	ft_print_array_triple(data->inputs->splitaftpipes); // Borrar mas adelante.	
	free_array(data->inputs->splitpipes);
	return (1);
}

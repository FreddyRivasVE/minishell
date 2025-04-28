/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:46:39 by frivas            #+#    #+#             */
/*   Updated: 2025/04/28 17:47:09 by frivas           ###   ########.fr       */
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
		commands[i] = ft_split_quotes(temp[i], false);
		if (!commands[i])
			return (free_triple_array(commands), NULL);
		i++;
	}
	commands[i] = NULL;
	data->pipesnum = i - 1;
	return (commands);
}

void	ms_split_input(t_mshell *data)
{
	data->inputs = malloc(sizeof(t_input));
	if (!data->inputs)
		return ;
	data->commands = malloc(sizeof(t_command));
	if (!data->commands)
		return ;
	data->inputs->splitpipes = ft_split_pipes(data->input_row);
	if (!data->inputs->splitpipes)
		return ;
	data->inputs->splitaftpipes = ms_split_postpipe(data);
	if (!data->inputs->splitaftpipes)
		return ;
	ms_expand_variable(data);
	ms_quotes_killer(data->inputs->splitaftpipes);
	printf("luego de expandir ----->\n"); // borrar.
	ft_print_array_triple(data->inputs->splitaftpipes); //borrar.
	ms_token_input(data);
	ft_print_array(data->inputs->tag); //borrar.
	//ms_pre_redir(data);
	//ft_print_array(data->inputs->tag); //borrar.
	ms_pre_commands(data);
	free_array(data->inputs->splitpipes);
	return ;
}

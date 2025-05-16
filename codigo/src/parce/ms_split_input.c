/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:46:39 by frivas            #+#    #+#             */
/*   Updated: 2025/05/16 15:11:13 by frivas           ###   ########.fr       */
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
			return (ft_free_triple_array(commands), free_array(temp), NULL);
		i++;
	}
	commands[i] = NULL;
	data->pipesnum = i - 1;
	return (commands);
}

static void	ms_free_struct(t_mshell	*data)
{
	if (data->inputs->splitpipes)
		free_array(data->inputs->splitpipes);
	if (data->inputs->splitaftpipes)
		ft_free_triple_array(data->inputs->splitaftpipes);
	if (data->inputs->tag)
		free(data->inputs->tag);
	if (data->inputs)
		free(data->inputs);
}

bool	ms_split_input(t_mshell *data)
{
	data->inputs = malloc(sizeof(t_input));
	if (!data->inputs)
		return (ms_print_perror_malloc(data), false);
	data->inputs->splitpipes = ft_split_pipes(data->input_row);
	if (!data->inputs->splitpipes)
		return (free(data->inputs), ms_print_perror_malloc(data), false);
	data->inputs->splitaftpipes = ms_split_postpipe(data);
	if (!data->inputs->splitaftpipes)
		return (free(data->inputs), ms_print_perror_malloc(data), false);
	data->commands = ft_calloc(data->pipesnum + 2, sizeof(t_command));
	if (!data->commands)
		return (ms_free_struct(data), ms_print_perror_malloc(data), false);
	data->redir = ft_calloc(data->pipesnum + 2, sizeof(t_redir));
	if (!data->redir)
		return (ms_free_struct(data), ms_print_perror_malloc(data), false);
	if (!ms_quotes_killer(data->inputs->splitaftpipes, data))
		return (ms_free_struct(data), false);
	if (!ms_token_input(data))
		return (ms_free_struct(data), false);
	if (!ms_orquest(data, data->inputs->splitaftpipes, data->inputs->tag))
		return (ms_free_struct(data), false);
	ms_free_struct(data);
	return (true);
}

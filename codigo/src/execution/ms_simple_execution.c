/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_simple_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:41:17 by frivas            #+#    #+#             */
/*   Updated: 2025/05/08 16:15:59 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_simple_execution_input(t_mshell *data)
{
	if (data->commands[0].input_name != NULL
		&& ft_strcmp(data->commands[0].input_name, "HEREDOC"))
	{
		data->commands[0].fd_input = open(data->commands[0].input_name, \
		O_RDONLY);
		if (data->commands[0].fd_input == -1)
		{
			perror(data->commands[0].input_name);
			data->exits = 1;
			return ;
		}
	}
	if (data->commands[0].input_name != NULL)
	{
		if (dup2(data->commands[0].fd_input, STDIN_FILENO) == -1)
		{
			perror(data->commands[0].input_name);
			data->exits = 1;
			return ;
		}
		close(data->commands[0].fd_input);
	}
}

void	ms_simple_execution_output(t_mshell *data)
{
	if (data->commands[0].type_output != NULL
		&& (!ft_strcmp(data->commands[0].type_output, "OUTPUT")
		|| !ft_strcmp(data->commands[0].type_output, "OUTPUTAPPEND")))
	{
		if (!ft_strcmp(data->commands[0].type_output, "OUTPUT"))
			data->commands[0].fd_output = open(data->commands[0].output_name, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			data->commands[0].fd_output = open(data->commands[0].output_name, \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (data->commands[0].fd_output == -1)
		{
			perror(data->commands[0].output_name);
			data->exits = 1;
			return ;
		}
		if (dup2(data->commands[0].fd_output, STDOUT_FILENO) == -1)
		{
			perror(data->commands[0].output_name);
			data->exits = 1;
			return ;
		}
		close(data->commands[0].fd_output);
	}
}

void	ms_simple_execution(t_mshell *data)
{
	ms_simple_execution_input(data);
	ms_simple_execution_output(data);
	data->exits = ms_exec_builtin_or_other(data->commands[0].command, data);
}

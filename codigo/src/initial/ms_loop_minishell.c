/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_loop_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:57:42 by frivas            #+#    #+#             */
/*   Updated: 2025/05/13 15:27:28 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec(t_mshell *data)
{
	if (!ms_redir_management(data))
	{
		ft_free_redir_array(data->redir);
		ft_free_command_array(data->commands, data->pipesnum + 1);
		return ;
	}
	ft_print_redir_array(data->redir); //borrar
	ft_print_command_array(data->commands, data->pipesnum + 1); //borrar
	if (data->pipesnum != 0)
		run_pipeline(data->commands, data->pipesnum + 1, data);
	else
		ms_simple_execution(data);
	ft_free_redir_array(data->redir);
	ft_free_command_array(data->commands, data->pipesnum + 1);
	return ;
}

bool	ms_parcetoken_mini(t_mshell *data, char *read_line)
{
	int		door;

	if (data->input_row)
		ft_free_ptr((void **)&data->input_row);
	data->input_row = ft_substr(read_line, 0, ft_strlen(read_line));
	door = ms_input_row_validation(data);
	if (door == 0)
	{
		if (ft_strchr(data->input_row, '$'))
		{
			if (!ms_special_expand(data))
				return (false);
		}
		if (ft_strchr(data->input_row, '<') || ft_strchr(data->input_row, '>'))
		{
			if (!ms_redir_together(data))
				return (false);
		}
		if (!ms_split_input(data))
			return (false);
	}
	data->exits = door;
	if (door != 0)
		return (false);
	return (true);
}

void	ms_update_signal(t_mshell *data)
{
	if (g_signal == SIGINT)
	{
		data->exits = 128 + g_signal;
		g_signal = 0;
	}
}

void	ms_loop_minishell(t_mshell *data)
{
	char	*read_line;

	data->input_row = NULL;
	while (1)
	{
		ms_set_signal_handler(MODE_PROMPT);
		read_line = readline(data->prompt);
		if (!read_line)
		{
			ms_exit_minishell(data);
			break ;
		}
		ms_update_signal(data);
		if (*read_line)
		{
			add_history(read_line);
			if (!ms_parcetoken_mini(data, read_line))
			{
				free(read_line);
				continue ;
			}
			ms_exec(data);
		}
		free(read_line);
	}
}

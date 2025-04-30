/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_loop_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:57:42 by frivas            #+#    #+#             */
/*   Updated: 2025/04/30 18:55:54 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exec(t_mshell *data)
{
	int		exit;

	printf("luego de expandir ----->\n"); // borrar.
	ft_print_array_triple(data->inputs->splitaftpipes); //borrar.
	exit = ms_exec_builtin_or_other(data->inputs->splitaftpipes, data, 0);
	free_triple_array(data->inputs->splitaftpipes);
	free(data->inputs);
	if (data->commands)
		free(data->commands);
	return (exit);
}

void	ms_exit_minishell(t_mshell *data)
{
	printf("exit\n");
	ft_lstclear(&data->env, free);
	ft_free_ptr((void **)&data->prompt);
	ft_free_ptr((void **)&data->input_row);
	rl_clear_history();
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
	return (true);
}

void	ms_loop_minishell(t_mshell *data)
{
	char	*read_line;

	data->input_row = NULL;
	while (1)
	{
		read_line = readline(data->prompt);
		if (!read_line)
		{
			ms_exit_minishell(data);
			break ;
		}
		if (*read_line)
		{
			add_history(read_line);
			if (!ms_parcetoken_mini(data, read_line))
			{
				free(read_line);
				continue ;
			}
			data->exits = ms_exec(data);
		}
		free(read_line);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_loop_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:57:42 by frivas            #+#    #+#             */
/*   Updated: 2025/04/25 18:20:12 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exec(t_mshell *data)
{
	int		exit;

	exit = ms_exec_builtin_or_other(data->inputs->splitaftpipes, data, 0);
	free_triple_array(data->inputs->splitaftpipes);
	free(data->inputs);
	free(data->commands->redir.namefile);
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

int	ms_parcetoken_mini(t_mshell *data, char *read_line)
{
	char	*new_input;
	int		door;

	if (data->input_row)
		ft_free_ptr((void **)&data->input_row);
	data->input_row = ft_substr(read_line, 0, ft_strlen(read_line));
	door = ms_input_row_validation(data);
	if (door == 0)
	{
		if (ft_strchr(data->input_row, '$'))
		{
			new_input = ms_escape_special_chars(data->input_row);
			free(data->input_row);
			data->input_row = new_input;
		}
		if (ft_strchr(data->input_row, '<') || ft_strchr(data->input_row, '>'))
		{
			new_input = ms_redir_together(data->input_row);
			free(data->input_row);
			data->input_row = new_input;
		}
		ms_split_input(data);
		return (1);
	}
	data->exits = door;
	return (0);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_loop_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:57:42 by frivas            #+#    #+#             */
/*   Updated: 2025/04/05 20:14:50 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
solo para probar si funcionan los comandos
*/
int	ms_exec(char *input_row, t_mshell *data)
{
	char	**command;
	int		exit;

	command = ft_split(input_row, ' ');
	exit = ms_exec_builtin_or_other(command, data);
	free_array(command);
	return (exit);
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
			printf("exit\n");
			ft_lstclear(&data->env, free);
			ms_free_ptr((void *)data->prompt);
			ms_free_ptr((void *)data->input_row);
			rl_clear_history();
			break ;
		}
		if (*read_line)
		{
			add_history(read_line);
			if (data->input_row)
				ms_free_ptr((void *)data->input_row);
			data->input_row = ft_substr(read_line, 0, ft_strlen(read_line));
			data->exits = ms_input_row_validation(data);
			data->exits = ms_exec(data->input_row, data);
		}
		free(read_line);
	}
}

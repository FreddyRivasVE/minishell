/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_loop_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:57:42 by frivas            #+#    #+#             */
/*   Updated: 2025/04/03 16:16:52 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_loop_minishell(t_mshell *data)
{
	char	*read_line;

	data->inputrow = NULL;
	while (1)
	{
		read_line = readline(data->prompt);
		if (!read_line)
		{
			printf("exit\n");
			ft_lstclear(&data->env, free);
			free(data->prompt);
			free(data->inputrow);
			rl_clear_history();
			break ;
		}
		if (*read_line)
		{
			add_history(read_line);
			if (data->inputrow)
				free(data->inputrow);
			data->inputrow = ft_substr(read_line, 0, ft_strlen(read_line));
			data->exits = ms_input_row_validation(data);
		}
		free(read_line);
	}
}

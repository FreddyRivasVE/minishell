/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_loop_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:57:42 by frivas            #+#    #+#             */
/*   Updated: 2025/04/11 12:09:23 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exec(t_mshell *data)
{
	int		exit;

	if (!ms_split_input(data))
		return (ft_putendl_fd("minishell: malloc", 2), ENOMEM);
	exit = ms_exec_builtin_or_other(data->inputs->splitaftpipes, data, 0);
	free_triple_array(data->inputs->splitaftpipes);
	free(data->inputs);
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
			ft_free_ptr((void *)data->prompt);
			ft_free_ptr((void *)data->input_row);
			rl_clear_history();
			break ;
		}
		if (*read_line)
		{
			add_history(read_line);
			if (data->input_row)
				ft_free_ptr((void *)data->input_row);
			data->input_row = ft_substr(read_line, 0, ft_strlen(read_line));
			data->exits = ms_input_row_validation(data);
			if (data->exits != 2)
				data->exits = ms_exec(data);
		}
		free(read_line);
	}
}

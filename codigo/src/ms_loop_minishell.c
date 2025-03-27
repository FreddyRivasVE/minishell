/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_loop_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:57:42 by frivas            #+#    #+#             */
/*   Updated: 2025/03/27 15:50:10 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_loop_minishell(t_mshell *data)
{
	char	*read_line;

	while (1)
	{
		read_line = readline(data->prompt);
		if (!read_line)
		{
			printf("exit\n");
			ft_lstclear(&data->env, free);
			free(data->prompt);
			break ;
		}
		if (*read_line)
			add_history(read_line);
		printf("Entrada: %s\n", read_line);
		free(read_line);
	}
}

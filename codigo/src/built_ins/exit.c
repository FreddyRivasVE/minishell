/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:45:41 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/05/12 10:35:05 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit_minishell(t_mshell *data)
{
	ft_putendl_fd("exit", 1);
	ft_lstclear(&data->env, free);
	ft_free_ptr((void **)&data->prompt);
	ft_free_ptr((void **)&data->input_row);
	rl_clear_history();
}

int	ms_exit(char **command, t_mshell *data)
{
	int	i;
	int	num;
	
	i = 1;
	num = 0;
	if (!command[i])
	{
		close(data->inistdin);
		close(data->inistdout);
		ft_free_redir_array(data->redir);
		ft_free_command_array(data->commands, data->pipesnum + 1);
		ms_exit_minishell(data);
		exit(num);
	}
	
	return (num);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:45:41 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/05/11 13:36:11 by brivera          ###   ########.fr       */
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
		ft_free_redir_array(data->redir);
		ft_free_command_array(data->commands, data->pipesnum + 1);
		ms_exit_minishell(data);
		exit(num);
	}
	
	return (num);
}

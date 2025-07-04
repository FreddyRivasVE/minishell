/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_memory_child.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:40:57 by brivera           #+#    #+#             */
/*   Updated: 2025/06/02 15:32:24 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_free_child(char *msm, t_mshell *data, int flag)
{
	if (flag == 0)
	{
		perror(msm);
		close_all_pipes(data->commands, data->pipesnum + 1);
	}
	ft_free_redir_array(data->redir);
	ft_free_command_array(data->commands, data->pipesnum + 1);
	ft_lstclear(&data->env, free);
	ft_free_ptr((void **)&data->prompt);
	ft_free_ptr((void **)&data->input_row);
	rl_clear_history();
	if (flag == 0)
		exit(1);
}

void	ms_close(t_mshell *data)
{
	close(data->inistdin);
	close(data->inistdout);
}

void	ms_free_onecommand(char	**command, t_mshell *data, char *msm)
{
	ms_close(data);
	ms_free_command_child(command, data, msm);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:40 by frivas            #+#    #+#             */
/*   Updated: 2025/05/12 19:59:35 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_child_management(t_mshell *data, int i)
{
	pid_t	pid;
	
	pid = fork();
	if (pid != 0)
		return (pid);
	ms_set_signal_handler(MODE_CHILD);
	data->inistdout = dup(STDOUT_FILENO);
	if (i != 0)
	{
		if (dup2(data->commands[i - 1].fd_output, STDIN_FILENO) == -1)
		{
			perror("dup");
			exit (1);
		}
	}
	if (i == data->pipesnum)
	{
		if (dup2(data->inistdout, STDOUT_FILENO))
		{
			perror("dup");
			exit (1);
		}
		else
		{
			if (dup2(data->commands[i].pipefd[1], STDOUT_FILENO))
			{
				perror("dup");
				exit (1);
			}
		}
	}
	ms_exec_builtin_or_other(data->commands[i].command, data);
	return (0);
}

void	ms_pipe_management(t_mshell *data)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i <= data->pipesnum)
	{
		if (pipe(data->commands[i].pipefd) == -1)
		{
			perror("pipe");
			data->exits = 1;
			return ;
		}
		pid = ms_child_management(data, i);
		signal(SIGINT, SIG_IGN);
		i++;
	}
	while (waitpid(pid, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			data->exits = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exits = 128 + WTERMSIG(status);
	}
	ms_set_signal_handler(MODE_PROMPT);
}

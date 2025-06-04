/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:40 by frivas            #+#    #+#             */
/*   Updated: 2025/06/04 11:39:13 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_pipes(t_command *cmds, int total)
{
	int	i;

	i = 0;
	while (i < total)
	{
		if (cmds[i].pipefd[0] != -1)
		{
			if (!close(cmds[i].pipefd[0]))
				cmds[i].pipefd[0] = -1;
		}
		if (cmds[i].pipefd[1] != -1)
		{
			if (!close(cmds[i].pipefd[1]))
				cmds[i].pipefd[1] = -1;
		}
		i++;
	}
}

static void	exec_child(t_command *cmds, int i, int total, t_mshell *data)
{
	t_command	*cmd;

	cmd = &cmds[i];
	ms_redirect_child_input(cmds, i, data);
	ms_redirect_child_output(cmds, i, total, data);
	data->exits = ms_exec_builtin_or_other(cmds[i].command, data);
	close_all_pipes(cmds, total);
	ms_free_child(cmd->input_name, data, 1);
	exit(data->exits);
}

static void	ms_wait_childs(t_mshell *data, int cmd_len)
{
	int	i;
	int	status;

	i = 0;
	signal(SIGINT, SIG_IGN);
	while (i < cmd_len)
	{
		waitpid(data->commands[i].pid, &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		data->exits = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		write(1, "\n", 1);
		data->exits = 128 + WTERMSIG(status);
	}
}

static int	ms_open_pipe(t_command *cmds, int i, int cmd_len, t_mshell *data)
{
	if (i < (cmd_len - 1))
	{
		if (pipe(cmds[i].pipefd) == -1)
		{
			perror("pipe");
			data->exits = 1;
			return (-1);
		}
	}
	else
	{
		cmds[i].pipefd[0] = -1;
		cmds[i].pipefd[1] = -1;
	}
	return (0);
}

void	ms_run_pipeline(t_command *commands, int cmd_len, t_mshell *data)
{
	int		i;

	i = 0;
	while (i < cmd_len)
	{
		if (ms_open_pipe(commands, i, cmd_len, data) == -1)
			return ;
		commands[i].pid = fork();
		if (commands[i].pid == -1)
		{
			perror("fork");
			data->exits = 1;
			return ;
		}
		if (commands[i].pid == 0)
			exec_child(commands, i, cmd_len, data);
		if (i < (cmd_len - 1))
			close(commands[i].pipefd[1]);
		if (i > 0)
			close(commands[i - 1].pipefd[0]);
		i++;
	}
	close_all_pipes(commands, cmd_len);
	ms_wait_childs(data, cmd_len);
	ms_set_signal_handler(MODE_PROMPT);
}

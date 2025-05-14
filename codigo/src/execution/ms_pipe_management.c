/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:40 by frivas            #+#    #+#             */
/*   Updated: 2025/05/14 16:12:03 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	ms_child_management(t_mshell *data, int i)
{
	char	*buff;
	
	buff = ft_calloc(1024, sizeof(char));
	if (pipe(data->commands[i].pipefd) == -1)
	{
		perror("pipe");
		data->exits = 1;
		return (-1);
	}
	data->commands[i].pid = fork();
	if (data->commands[i].pid == -1)
		return (-1);
	ms_set_signal_handler(MODE_CHILD);
	if (data->commands[i].pid == 0)
	{
		//close(data->commands[i].pipefd[0]);
		if (dup2(data->commands[i].pipefd[1], STDOUT_FILENO) == -1)
		{
			printf("dup: %d\n", data->commands[i].pipefd[1]);
			perror("dup2");
			exit(1);
		}
		close(data->commands[i].pipefd[1]);
		read(data->commands[i].pipefd[0], buff, 1024);
		printf("%s\n", buff);// borrar
		ms_exec_builtin_or_other(data->commands[i].command, data);
	}
	close(data->commands[i].pipefd[1]);
	if (dup2(data->commands[i].pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		data->exits = 1;
		return (-1);
	}
	close(data->commands[i].pipefd[0]);
	return (0);
}

int	ms_last_child(t_mshell *data, int i)
{
	data->commands[i].pid = fork();
	if (data->commands[i].pid == -1)
		return (-1);
	ms_set_signal_handler(MODE_CHILD);
	if (data->commands[i].pid == 0)
		ms_exec_builtin_or_other(data->commands[i].command, data);
	return (0);
}

void	ms_pipe_management(t_mshell *data)
{
	int		i;
	int		status;
	int		inistdin;

	inistdin = dup(STDIN_FILENO);
	if (inistdin == -1)
	{
		perror("dup");
		data->exits = 1;
	}
	i = 0;
	while (i < data->pipesnum)
	{
		signal(SIGINT, SIG_IGN);
		if (ms_child_management(data, i) == -1)
			return ;
		i++;
	}
	if (ms_last_child(data, i))
		return ;
	if (dup2(inistdin, STDIN_FILENO) == -1)
	{
		perror("dup2");
		data->exits = 1;
	}
	close(inistdin);
	i = 0;
	while (i <= data->pipesnum)
	{
		waitpid(data->commands[i].pid, &status, 0);
		if (WIFEXITED(status))
			data->exits = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exits = 128 + WTERMSIG(status);
		i++;
	}
	ms_set_signal_handler(MODE_PROMPT);
}
*/

void	open_input(t_command *cmd)
{
	if (!cmd->input_name)
		return ;
	cmd->fd_input = open(cmd->input_name, O_RDONLY);
	if (cmd->fd_input < 0)
	{
		perror("open input");
		exit(EXIT_FAILURE);
	}
}

void	open_output(t_command *cmd)
{
	if (!cmd->output_name)
		return ;
	if (cmd->type_output && cmd->type_output[0] == 'A')
		cmd->fd_output = open(cmd->output_name, O_WRONLY | O_CREAT
				| O_APPEND, 0644);
	else
		cmd->fd_output = open(cmd->output_name, O_WRONLY | O_CREAT
				| O_TRUNC, 0644);
	if (cmd->fd_output < 0)
	{
		perror("open output");
		exit(EXIT_FAILURE);
	}
}

void	close_all_pipes(t_command *cmds, int total)
{
	int	i;

	i = 0;
	while (i < total)
	{
		if (cmds[i].pipefd[0] != -1)
			close(cmds[i].pipefd[0]);
		if (cmds[i].pipefd[1] != -1)
			close(cmds[i].pipefd[1]);
		i++;
	}
}

void	exec_child(t_command *cmds, int i, int total, t_mshell *data)
{
	t_command	*cmd;
	char		*readline;

	readline = ft_calloc(1024, sizeof(char));
	cmd = &cmds[i];
	open_input(cmd);
	open_output(cmd);

	if (cmd->input_name)
		dup2(cmd->fd_input, STDIN_FILENO);
	else if (i > 0)
	{
		dup2(cmds[i - 1].pipefd[0], STDIN_FILENO);
		close(cmds[i - 1].pipefd[0]);
	}
	if (cmd->output_name)
		dup2(cmd->fd_output, STDOUT_FILENO);
	else if (i < (total - 1))
	{
		dup2(cmd->pipefd[1], STDOUT_FILENO);
		close(cmd->pipefd[1]);
	}
	if (i > 0)
	{
		if (cmds[i - 1].pipefd[0] != -1)
			close(cmds[i - 1].pipefd[0]);
	}
	data->exits = ms_exec_builtin_or_other(cmds[i].command, data);
	exit(data->exits);
}


void	run_pipeline(t_command *commands, int cmd_len, t_mshell *data)
{
	int		i;

	i = 0;
	while (i < cmd_len)
	{
		if (i < cmd_len - 1)
		{
			if (pipe(commands[i].pipefd) == -1)
			{
				perror("pipe");
				data->exits = 1;
				return ;
			}
		}
		else
		{
			commands[i].pipefd[0] = -1;
			commands[i].pipefd[1] = -1;
		}
		commands[i].pid = fork();
		if (commands[i].pid == -1)
		{
			perror("fork");
			data->exits = 1;
		}
		if (commands[i].pid == 0)
			exec_child(commands, i, cmd_len, data);
		if (i < cmd_len - 1)
			close(commands[i].pipefd[1]);
		i++;
	}
	i = 0;
	close_all_pipes(commands, cmd_len);
	while (i < cmd_len)
	{
		waitpid(commands[i].pid, NULL, 0);
		i++;
	}
}


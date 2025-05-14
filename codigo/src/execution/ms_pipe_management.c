/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:10:40 by frivas            #+#    #+#             */
/*   Updated: 2025/05/14 17:49:50 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_free_child(char *msm, t_mshell *data)
{
	perror(msm);
	ft_free_redir_array(data->redir);
	ft_free_command_array(data->commands, data->pipesnum + 1);
	ft_lstclear(&data->env, free);
	ft_free_ptr((void **)&data->prompt);
	ft_free_ptr((void **)&data->input_row);
	rl_clear_history();
	exit(1);
}

void	open_input(t_command *cmd, t_mshell *data)
{
	if (!cmd->input_name)
		return ;
	if (cmd->input_name != NULL
		&& ft_strcmp(cmd->input_name, "HEREDOC"))
	{
		cmd->fd_input = open(cmd->input_name, \
		O_RDONLY);
		if (cmd->fd_input == -1)
			ms_free_child(cmd->input_name, data);
	}
}

void	open_output(t_command *cmd, t_mshell *data)
{
	(void) data;
	if (!cmd->output_name)
		return ;
	if (cmd->type_output != NULL
		&& (!ft_strcmp(cmd->type_output, "OUTPUT")
			|| !ft_strcmp(cmd->type_output, "OUTPUTAPPEND")))
	{
		if (!ft_strcmp(cmd->type_output, "OUTPUT"))
			cmd->fd_output = open(cmd->output_name, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			cmd->fd_output = open(cmd->output_name, \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->fd_output == -1)
			ms_free_child(cmd->output_name, data);
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

	cmd = &cmds[i];
	open_input(cmd, data);
	open_output(cmd, data);
	if (cmd->input_name)
	{
		dup2(cmd->fd_input, STDIN_FILENO);
		close(cmd->fd_input);
	}
	else if (i > 0)
	{
		dup2(cmds[i - 1].pipefd[0], STDIN_FILENO);
		close(cmds[i - 1].pipefd[0]);
	}
	if (cmd->output_name)
	{
		dup2(cmd->fd_output, STDOUT_FILENO);
		close(cmd->fd_output);
	}
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
	int		status;

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
	signal(SIGINT, SIG_IGN);
	while (i < cmd_len)
	{
		waitpid(commands[i].pid, &status, 0);
		if (WIFEXITED(status))
			data->exits = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			write(1,"\n", 1);
			data->exits = 128 + WTERMSIG(status);
			break ;
		}
		i++;
	}
	ms_set_signal_handler(MODE_PROMPT);
}

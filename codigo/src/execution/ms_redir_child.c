/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:16:35 by frivas            #+#    #+#             */
/*   Updated: 2025/06/04 11:09:14 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_input(t_command *cmd, t_mshell *data)
{
	if (!cmd->input_name)
		return ;
	if (cmd->input_name != NULL
		&& ft_strcmp(cmd->input_name, "HEREDOC")
		&& ft_strcmp(cmd->input_name, "HEREDOCNE"))
	{
		cmd->fd_input = open(cmd->input_name, O_RDONLY);
		if (cmd->fd_input == -1)
			ms_free_child(cmd->input_name, data, 0);
	}
}

static void	open_output(t_command *cmd, t_mshell *data)
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
			ms_free_child(cmd->output_name, data, 0);
	}
}

void	ms_redirect_child_input(t_command *cmds, int i, t_mshell *data)
{
	t_command	*cmd;

	cmd = &cmds[i];
	open_input(cmd, data);
	if (cmd->input_name)
	{
		if (dup2(cmd->fd_input, STDIN_FILENO) == -1)
			ms_free_child(cmd->input_name, data, 0);
		close(cmd->fd_input);
		if (i > 0)
			close(cmds[i - 1].pipefd[0]);
	}
	else if (i > 0)
	{
		if (dup2(cmds[i - 1].pipefd[0], STDIN_FILENO) == -1)
			ms_free_child(cmd->input_name, data, 0);
		close(cmds[i - 1].pipefd[0]);
	}
	if (cmd->pipefd[0] != -1)
		close(cmd->pipefd[0]);
}

void	ms_redirect_child_output(t_command *cmds, int i, int total, \
	t_mshell *data)
{
	t_command	*cmd;

	cmd = &cmds[i];
	open_output(cmd, data);
	if (cmd->output_name)
	{
		if (dup2(cmd->fd_output, STDOUT_FILENO) == -1)
			ms_free_child(cmd->input_name, data, 0);
		close(cmd->fd_output);
		if (cmd->pipefd[1] != -1)
			close(cmd->pipefd[1]);
	}
	else if (i < (total - 1))
	{
		if (dup2(cmd->pipefd[1], STDOUT_FILENO) == -1)
			ms_free_child(cmd->input_name, data, 0);
		close(cmd->pipefd[1]);
	}
}

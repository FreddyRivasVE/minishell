/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_other_onecommand.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:08:12 by brivera           #+#    #+#             */
/*   Updated: 2025/05/14 19:09:04 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_free_onecommand(char	**command, t_mshell *data, char *msm)
{
	close(data->inistdin);
	close(data->inistdout);
	ms_free_command_child(command, data, msm);
}

static int	ms_free_child_pipe(char **command, t_mshell *data, char *msm)
{
	int		cod_error;

	free_array(data->envp);
	if (!ft_strcmp(msm, ERROCOMMAND))
	{
		ft_print_error(MINI, command[0], msm);
		return (127);
	}
	else
	{
		if (access(command[0], F_OK) == -1)
		{
			ft_print_error(MINI, command[0], msm);
			cod_error = 127;
		}
		else
		{
			ft_print_error(MINI, command[0], ERRORPERMISSION);
			cod_error = 126;
		}
	}
	return (cod_error);
}

static int	ms_exec_pipes(char **command, t_mshell *data)
{
	char	*path;

	path = NULL;
	if (ft_strlen(command[0]) == 0)
		ms_free_command_point(command, data, ERROCOMMANDSL, 127);
	if (!ft_strcmp(command[0], "."))
		ms_free_command_point(command, data, ERRORP, 2);
	if (ft_strchr(command[0], '/'))
	{
		if (access(command[0], F_OK | X_OK) == 0)
			path = ft_strdup(command[0]);
		else
			return (ms_free_child_pipe(command, data, NOFILEDIRCTORY));
	}
	else
	{
		path = ms_recoverpath(command[0], &data->env, data);
		if (!path && data->exits != ENOMEM)
			return (ms_free_child_pipe(command, data, ERROCOMMAND));
		else if (data->exits == ENOMEM)
			return (ENOMEM);
	}
	return (ms_execute_command_pipe(path, command, data->envp));
}

static int	ms_exec_other_onecommand(char **command, t_mshell *data)
{
	char	*path;
	pid_t	pid;

	pid = fork();
	if (pid != 0)
		return (pid);
	path = NULL;
	if (ft_strlen(command[0]) == 0)
		ms_free_onecommand(command, data, ERROCOMMANDSL);
	if (ft_strchr(command[0], '/'))
	{
		if (access(command[0], F_OK | X_OK) == 0)
			path = ft_strdup(command[0]);
		else
			ms_free_onecommand(command, data, NOFILEDIRCTORY);
	}
	else
	{
		path = ms_recoverpath(command[0], &data->env, data);
		if (!path && data->exits != ENOMEM)
			ms_free_onecommand(command, data, ERROCOMMAND);
		else if (data->exits == ENOMEM)
			exit(ENOMEM);
	}
	return (ms_execute_command(path, command, data->envp, data), 0);
}

int	ms_exec_other(char **command, t_mshell *data)
{
	int		status;
	pid_t	pid;

	ms_move_env_to_pointer(data);
	if (data->exits == ENOMEM)
		return (ENOMEM);
	if (data->pipesnum == 0)
	{
		if (!ft_strcmp(command[0], "."))
			return (free_array(data->envp), \
			ft_print_error(MINI, command[0], ERRORP), 2);
		pid = ms_exec_other_onecommand(command, data);
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		free_array(data->envp);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (ft_putstr_fd("\n", 1), 128 + WTERMSIG(status));
		ms_set_signal_handler(MODE_PROMPT);
	}
	else
		return (ms_exec_pipes(command, data));
	return (0);
}

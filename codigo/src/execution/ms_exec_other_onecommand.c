/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_other_onecommand.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:08:12 by brivera           #+#    #+#             */
/*   Updated: 2025/05/13 16:41:20 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_move_env_to_pointer(t_mshell *data)
{
	int		count;
	t_list	*current;
	int		i;

	i = 0;
	count = ft_lstsize(data->env);
	data->envp = ft_calloc(count + 1, sizeof(char *));
	if (!data->envp)
	{
		ms_print_perror_malloc(data);
		return ;
	}
	current = data->env;
	//while (current != NULL && current->next != NULL)
	while (current != NULL)
	{
		data->envp[i] = ft_strdup(current->content);
		if (!data->envp[i])
		{
			ms_print_perror_malloc(data);
			free_array(data->envp);
			return ;
		}
		i++;
		current = current->next;
	}
}

static int	ms_exec_other_onecommand(char **command, t_mshell *data)
{
	char	*path;
	pid_t	pid;

	pid = fork();
	if (pid != 0)
		return (pid);
	ms_set_signal_handler(MODE_CHILD);
	path = NULL;
	if (ft_strchr(command[0], '/'))
	{
		if (access(command[0], F_OK | X_OK) == 0)
			path = ft_strdup(command[0]);
		else
			ft_error_and_exit(MINI, command[0], NOFILEDIRCTORY, 127);
	}
	else
	{
		path = ms_recoverpath(command[0], &data->env, data);
		if (!path && data->exits != ENOMEM)
			ft_error_and_exit(MINI, command[0], ERROCOMMAND, 127);
		else if (data->exits == ENOMEM)
			exit(ENOMEM);
	}
	ms_execute_command(path, command, data->envp);
	return (0);
}

int	ms_exec_pipes(char **command, t_mshell *data)
{
	char	*path;

	path = NULL;
	if (ft_strchr(command[0], '/'))
	{
		if (access(command[0], F_OK | X_OK) == 0)
			path = ft_strdup(command[0]);
		else
			ft_error_and_exit(MINI, command[0], NOFILEDIRCTORY, 127);
	}
	else
	{
		path = ms_recoverpath(command[0], &data->env, data);
		if (!path && data->exits != ENOMEM)
			ft_error_and_exit(MINI, command[0], ERROCOMMAND, 127);
		else if (data->exits == ENOMEM)
			exit(ENOMEM);
	}
	ms_execute_command(path, command, data->envp);
	return (0);
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
	{
		ms_exec_pipes(command, data);
		free_array(data->envp);
	}
	return (0);
}

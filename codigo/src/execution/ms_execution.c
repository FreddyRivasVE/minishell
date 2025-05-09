/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:15:12 by brivera           #+#    #+#             */
/*   Updated: 2025/05/09 13:07:54 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_recoverpath(char *commands, t_list **env)
{
	int		i;
	char	**paths;
	char	*path;
	char	*part_path;

	i = 0;
	path = ft_list_extract_if(env, "PATH", var_cmp);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (ft_free_ptr((void **)&path), NULL);
	i = 0;
	ft_free_ptr((void **)&path);
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, commands);
		if (access(path, F_OK | X_OK) == 0)
			return (free_array(paths), path);
		ft_free_ptr((void **)&path);
		i++;
	}
	return (free_array(paths), NULL);
}

static void	ms_move_env_to_pointer(t_mshell *data)
{
	int		count;
	t_list	*current;
	int		i;

	i = 0;
	count = ft_lstsize(data->env);
	data->envp = ft_calloc(count + 1, sizeof(char *));
	if (!data->envp)
		ms_print_perror_malloc(data);
	current = data->env;
	while (current != NULL && current->next != NULL)
	{
		data->envp[i] = ft_strdup(current->content);
		i++;
		current = current->next;
	}
}

int	ms_exec_other(char **command, t_mshell *data)
{
	char	*path;
	pid_t	pid;

	pid = fork();
	if (pid != 0)
		return (pid);
	ms_set_signal_handler(MODE_CHILD);
	ms_move_env_to_pointer(data);
	if (ft_strchr(command[0], '/'))
	{
		if (access(command[0], F_OK | X_OK) == 0)
			path = ft_strdup(command[0]);
		else
			exit(127);
	}
	else
	{
		path = ms_recoverpath(command[0], &data->env);
		if (!path)
			exit(127);
	}
	if (execve(path, command, data->envp) == -1)
	{
		perror(command[0]);
		exit(127);
	}
	exit(0);
}

int	ms_exec_builtin_or_other(char **command, t_mshell *data)
{
	int		status;
	pid_t	pid;

	if (!command || !command[0])
		return (0);
	if (!ft_strncmp(command[0], "echo", 5))
		return (ms_echo(command));
	else if (!ft_strncmp(command[0], "cd", 3))
		return (ms_cd(command, &data->env, data));
	else if (!ft_strncmp(command[0], "pwd", 4))
		return (ms_pwd(command, &data->env));
	else if (!ft_strncmp(command[0], "export", 7))
		return (ms_export(command, data));
	else if (!ft_strncmp(command[0], "unset", 6))
		ms_unset(data, command);
	else if (!ft_strncmp(command[0], "env", 4))
		return (ms_env(command, &data->env));
	else if (!ft_strncmp(command[0], "exit", 5))
		ms_exit(data);
	else
	{
		pid = ms_exec_other(command, data);
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			write(1, "\n", 1);
			return (128 + WTERMSIG(status));
		}
		ms_set_signal_handler(MODE_PROMPT);
	}
	return (0);
}

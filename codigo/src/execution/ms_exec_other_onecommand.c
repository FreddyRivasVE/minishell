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

char	*ms_kill_dquotes_v2(char *str)
{
	char	*result;
	int		i;
	int		j;
	int		flag;

	flag = 0;
	result = ft_calloc(ft_strlen(str) - 2, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != 0 )
	{
		if (str[i] == '\"' && str[i + 1] == '\0')
			break ;
		else
			result[j] = str[i];
		if (str[i] == '=' && flag == 0)
		{
			i++;
			flag = 1;
		}
		i++;
		j++;
	}
	return (result);
}

static void	ms_move_env_to_pointer(t_mshell *data)
{
	int		count;
	t_list	*lst;
	int		i;

	i = 0;
	count = ft_lstsize(data->env);
	data->envp = ft_calloc(count + 1, sizeof(char *));
	if (!data->envp)
	{
		ms_print_perror_malloc(data);
		return ;
	}
	lst = data->env;
	while (lst != NULL)
	{
		data->envp[i] = ms_kill_dquotes_v2(lst->content);
		if (!data->envp[i])
		{
			ms_print_perror_malloc(data);
			free_array(data->envp);
			return ;
		}
		i++;
		lst = lst->next;
	}
}

static void	ms_free_onecommand(char	**command, t_mshell *data, char *msm)
{
	close(data->inistdin);
	close(data->inistdout);
	ms_free_command_child(command, data, msm);
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
	return (ms_execute_command(path, command, data->envp), 0);
}

int	ms_free_command_child_pipe(char **command, t_mshell *data, char *msm)
{
	// (void) data;
	free_array(data->envp);
	ft_print_error(MINI, command[0], msm);
	//ms_free_child("", data, 1);
	return (127);
}

int	ms_exec_pipes(char **command, t_mshell *data)
{
	char	*path;

	path = NULL;
	if (ft_strlen(command[0]) == 0)
		ms_free_onecommand(command, data, ERROCOMMANDSL);
	if (ft_strchr(command[0], '/'))
	{
		if (access(command[0], F_OK | X_OK) == 0)
			path = ft_strdup(command[0]);
		else
			ms_free_command_child(command, data, NOFILEDIRCTORY);
	}
	else
	{
		path = ms_recoverpath(command[0], &data->env, data);
		if (!path && data->exits != ENOMEM)
			return(ms_free_command_child_pipe(command, data, ERROCOMMAND));
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
		return (ms_exec_pipes(command, data));
	return (0);
}

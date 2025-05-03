/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:15:12 by brivera           #+#    #+#             */
/*   Updated: 2025/05/03 11:51:36 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exec_other(char **command, t_list **env)
{
	(void) env;
	execve("/usr/bin/cat", command, NULL);
	return (0);
}

int	ms_exec_builtin_or_other(char **command, t_mshell *data)
{
	if (!command || !command[0])
	{
		printf("-----> comando a ejecutar: %s\n", command[0]);
		return (-1); // provisorio borrar 
	}
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
	//else
	//	ms_exec_other(command[i], &data->env);
	return (0);
}

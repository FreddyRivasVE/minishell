/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:15:12 by brivera           #+#    #+#             */
/*   Updated: 2025/04/19 18:12:56 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exec_other(char **command, t_list **env)
{
	(void)	env;

	execve("/usr/bin/ls", command, NULL);
	return (0);
}

int	ms_exec_builtin_or_other(char ***command, t_mshell *data, int i)
{
	if (!command || !command[i][0])
	{
		printf("-----> comando a ejecutar: %s\n", command[i][0]);
		return (-1); // provisorio borrar 
	}
	if (!ft_strncmp(command[i][0], "echo", 5))
		return (ms_echo(command[i]));
	else if (!ft_strncmp(command[i][0], "cd", 3))
		return (ms_cd(command[i], &data->env, data));
	else if (!ft_strncmp(command[i][0], "pwd", 4))
		return (ms_pwd(command[i]));
	else if (!ft_strncmp(command[i][0], "export", 7))
		return (ms_export(command[i], data));
	else if (!ft_strncmp(command[i][0], "unset", 6))
		ms_unset(data, command[i]);
	else if (!ft_strncmp(command[i][0], "env", 4))
		return (ms_env(command[i], &data->env));
	else if (!ft_strncmp(command[i][0], "exit", 5))
		ms_exit(data);
	//else
	//	ms_exec_other(command[i], &data->env);
	return (0);
}

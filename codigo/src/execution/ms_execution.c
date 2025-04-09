/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:15:12 by brivera           #+#    #+#             */
/*   Updated: 2025/04/09 15:27:00 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_echo(void)
{
	printf("echo\n");
	return (0);
}

int	ms_cd(void)
{
	printf("cd\n");
	return (0);
}

int	ms_exec_other(void)
{
	printf("demas comandos\n");
	return (0);
}

int	ms_exec_builtin_or_other(char ***command, t_mshell *data, int i)
{
	if (!ft_strncmp(command[i][0], "echo", 5))
		ms_echo();
	else if (!ft_strncmp(command[i][0], "cd", 3))
		ms_cd();
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
	else
		ms_exec_other();
	return (0);
}

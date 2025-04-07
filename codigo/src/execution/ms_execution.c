/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:15:12 by brivera           #+#    #+#             */
/*   Updated: 2025/04/07 23:32:49 by frivas           ###   ########.fr       */
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

int	ms_pwd(void)
{
	char	*pwd;

	pwd = ms_get_cwd();
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	ms_exec_other(void)
{
	printf("demas comandos\n");
	return (0);
}

int	ms_exec_builtin_or_other(char ***command, t_mshell *data)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (!command[i][0])
		{
			i++;
			continue ;
		}
		if (!ft_strncmp(command[0][0], "echo", 5))
			ms_echo();
		else if (!ft_strncmp(command[0][0], "cd", 3))
			ms_cd();
		else if (!ft_strncmp(command[0][0], "pwd", 4))
			ms_pwd();
		else if (!ft_strncmp(command[0][0], "export", 7))
			data->exits = ms_export(command[i], data);
		else if (!ft_strncmp(command[0][0], "unset", 6))
			ms_unset();
		else if (!ft_strncmp(command[0][0], "env", 4))
			data->exits = ms_env(command[i], &data->env);
		else if (!ft_strncmp(command[0][0], "exit", 5))
			ms_exit();
		else
			ms_exec_other();
		i++;
	}
	return (0);
}

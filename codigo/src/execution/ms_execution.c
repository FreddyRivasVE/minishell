/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:15:12 by brivera           #+#    #+#             */
/*   Updated: 2025/04/04 21:44:04 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec_builtin_or_other(char **command, t_mshell *data)
{
	if (!ft_strncmp(command[0], "echo", 5))
		ms_echo();
	else if (!ft_strncmp(command[0], "cd", 3))
		ms_cd();
	else if (!ft_strncmp(command[0], "pwd", 4))
		ms_pwd();
	else if (!ft_strncmp(command[0], "export", 7))
		data->exits->code = ms_export(command, data);
	else if (!ft_strncmp(command[0], "unset", 6))
		ms_unset();
	else if (!ft_strncmp(command[0], "env", 4))
		data->exits->code = ms_env(command, data->env);
	else if (!ft_strncmp(command[0], "exit", 5))
		ms_exit();
	else
		ms_exec_other(command, data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:15:12 by brivera           #+#    #+#             */
/*   Updated: 2025/04/01 21:10:49 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//env sin opciones o argumentos
void	ms_env(char **command, t_list **lst)
{
	if (command[1])
	{
		ft_putendl_fd("env: subject doesn't allow arguments or options", 2);
		return ;
	}
	print_list_content_char(lst);
}

//export sin opciones
void	ms_export(char **command, t_list **lst)
{
	if (command[1][0] == '-')
		return ;
	
}

void	ms_exec_builtin_or_other(char **command, t_mshell *data)
{
	if (!ft_strncmp(command[0], "echo", 5))
		ms_echo();
	else if (!ft_strncmp(command[0], "cd", 3))
		ms_cd();
	else if (!ft_strncmp(command[0], "pwd", 4))
		ms_pwd();
	else if (!ft_strncmp(command[0], "export", 7))
		ms_export(command, data->env);
	else if (!ft_strncmp(command[0], "unset", 6))
		ms_unset();
	else if (!ft_strncmp(command[0], "env", 4))
		ms_env(command, data->env);
	else if (!ft_strncmp(command[0], "exit", 5))
		ms_exit();
	else
		ms_exec_other(command, data);
}

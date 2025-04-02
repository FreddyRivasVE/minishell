/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:15:12 by brivera           #+#    #+#             */
/*   Updated: 2025/04/02 21:33:22 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//env sin opciones o argumentos
int	ms_env(char **command, t_list **lst)
{
	if (command[1])
	{
		ft_putendl_fd("env: subject doesn't allow arguments or options", 2);
		return (1);
	}
	print_list_content_char(lst);
	return (0);
}

//export sin opciones
int	ms_export(char **command, t_mshell *data)
{
	t_list	*new_node;
	char	*content;

	if (command[1])
	{
		if (command[1][0] == '-')
		{
			ft_putendl_fd("export: subject doesn't options", 2);
			return (1);
		}
		if (ft_isdigit(command[1][0]))
		{
			ft_putendl_fd("export: not an identifier", 2);
			return (1);
		}
		content = ft_strdup(command[1]);
		if (!content)
		{
			perror("malloc");
			return (1);
		}
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			perror("malloc");
			free(content);
			return (1);
		}
		ft_lstadd_back(&env_list, new_node);
	}
	else
		//solo escribieron el comando export
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

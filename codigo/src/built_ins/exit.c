/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:45:41 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/05/12 13:04:47 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_is_numeric(const char *str)
{
	if (!str || !*str)
		return (false);
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

void	ms_exit_minishell(t_mshell *data)
{
	ft_putendl_fd("exit", 1);
	ft_lstclear(&data->env, free);
	ft_free_ptr((void **)&data->prompt);
	ft_free_ptr((void **)&data->input_row);
	rl_clear_history();
}

static int	ms_handle_exit_code(char **command, t_mshell *data)
{
	int	exit_code;

	if (!command[1])
		return (data->exits);
	if (!ft_is_numeric(command[1]))
	{
		ft_print_error(MINI, command[0], ": numeric argument required");
		return (2);
	}
	if (command[2])
	{
		ft_print_error(MINI, command[0], ": too many arguments");
		return (1);
	}
	exit_code = ft_atoi(command[1]);
	if (exit_code > 256)
		exit_code %= 256;
	else if (exit_code < 0)
		exit_code = 256 + (exit_code % 256);
	return (exit_code);
}

int	ms_exit(char **command, t_mshell *data)
{
	close(data->inistdin);
	close(data->inistdout);
	ms_exit_minishell(data);
	data->exits = ms_handle_exit_code(command, data);
	ft_free_redir_array(data->redir);
	ft_free_command_array(data->commands, data->pipesnum + 1);
	exit(data->exits);
	return (0);
}

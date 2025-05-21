/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:42:14 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/05/14 19:15:24 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_error(char *arg, char	*var, char *msj)
{
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(var, 2);
	ft_putendl_fd(msj, 2);
}

void	ms_print_perror_malloc(t_mshell *data)
{
	data->exits = ENOMEM;
	perror("malloc");
}

void	ms_print_perror_exit(char *str, int num)
{
	perror(str);
	exit(num);
}

void	ms_free_command_child(char **command, t_mshell *data, char *msm)
{
	free_array(data->envp);
	ft_print_error(MINI, command[0], msm);
	ms_free_child("", data, 1);
	exit(127);
}

void	ms_free_child(char *msm, t_mshell *data, int flag)
{
	if (flag == 0)
		perror(msm);
	ft_free_redir_array(data->redir);
	ft_free_command_array(data->commands, data->pipesnum + 1);
	ft_lstclear(&data->env, free);
	ft_free_ptr((void **)&data->prompt);
	ft_free_ptr((void **)&data->input_row);
	rl_clear_history();
	if (flag == 0)
		exit(1);
}

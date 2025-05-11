/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:42:14 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/05/11 11:18:40 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_error(char *arg, char	*var, char *msj)
{
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(var, 2);
	ft_putendl_fd(msj, 2);
}

void	ft_error_and_exit(char *shell, char *command, char *msj, int num)
{
	ft_print_error(shell, command, msj);
	exit(num);
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

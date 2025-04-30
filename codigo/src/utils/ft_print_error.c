/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:42:14 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/04/30 16:59:30 by frivas           ###   ########.fr       */
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

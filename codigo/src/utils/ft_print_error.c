/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:42:14 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/04/21 19:42:32 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_error(char *arg, char	*var, char *msj)
{
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(var, 2);
	ft_putendl_fd(msj, 2);
}

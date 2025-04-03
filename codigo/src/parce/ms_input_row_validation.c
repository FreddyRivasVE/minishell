/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input_row_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:55:27 by frivas            #+#    #+#             */
/*   Updated: 2025/04/04 01:08:48 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//El error de sintaxis "<|>" ocurre porque
//es una secuencia no válida de operadores en Bash. 

int	ms_input_row_validation(t_mshell *data)
{
	if (!ms_check_quotation_marks(data->inputrow))
		return (ft_putendl_fd("minishell: syntax error", 2), 2);
	if (!ms_check_pipes(data->inputrow))
		return (ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2), 2);
	if (!ms_check_redir(data->inputrow))
		return (ft_putendl_fd("minishell: syntax error near unexpected token", 2), 2);
	ms_split_input(data->inputrow);
	return (0);
}

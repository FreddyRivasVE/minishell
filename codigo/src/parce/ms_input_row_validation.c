/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input_row_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:55:27 by frivas            #+#    #+#             */
/*   Updated: 2025/04/03 16:19:00 by brivera          ###   ########.fr       */
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
	return (0);
}

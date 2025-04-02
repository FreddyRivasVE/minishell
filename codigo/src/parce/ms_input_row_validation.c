/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input_row_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:55:27 by frivas            #+#    #+#             */
/*   Updated: 2025/04/02 17:45:40 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_input_row_validation(t_mshell *data)
{
	if (!ms_check_quotation_marks(data->inputrow))
		ft_putendl_fd("minishell: syntax error", 2);
	if (!ms_check_pipes(data->inputrow))
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
	if (!ms_check_redir(data->inputrow))
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input_row_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:55:27 by frivas            #+#    #+#             */
/*   Updated: 2025/04/06 17:26:05 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_input_row_validation(t_mshell *data)
{
	if (!ms_check_quotation_marks(data->input_row))
		return (ft_putendl_fd("minishell: syntax error", 2), 2);
	if (!ms_check_pipes(data->input_row))
		return (ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2), 2);
	if (!ms_check_redir(data->input_row))
		return (ft_putendl_fd("minishell: syntax error near unexpected token", 2), 2);
	if (!ms_split_input(data))
		return (ft_putendl_fd("minishell: malloc", 2), 2);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input_row_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:55:27 by frivas            #+#    #+#             */
/*   Updated: 2025/04/05 18:38:30 by brivera@stu      ###   ########.fr       */
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
	//ms_split_input(data->input_row);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input_row_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:55:27 by frivas            #+#    #+#             */
/*   Updated: 2025/04/30 16:34:05 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_input_row_validation(t_mshell *data)
{
	if (!data->input_row)
		return (ft_putendl_fd("malloc", 2), ENOMEM);
	if (!ms_check_quotation_marks(data->input_row))
		return (ft_putendl_fd(SYNTAX, 2), 2);
	if (!ms_check_pipes(data->input_row))
		return (ft_putendl_fd(SYNTAXPIPE, 2), 2);
	if (!ms_check_redir(data->input_row))
		return (ft_putendl_fd(SYNTAXREDIR, 2), 2);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input_row_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:55:27 by frivas            #+#    #+#             */
/*   Updated: 2025/04/02 12:58:49 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_input_row_validation(t_mshell *data)
{
	if (ms_check_quotation_marks(data->inputrow))
		printf("%s\n", data->inputrow);
	else
		ft_putendl_fd("minishell: syntax error", 2);
}

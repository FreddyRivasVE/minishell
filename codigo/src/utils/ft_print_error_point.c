/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error_point.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-24 14:28:43 by brivera           #+#    #+#             */
/*   Updated: 2025-05-24 14:28:43 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_free_command_point(char **command, t_mshell *data, char *msm, int e)
{
	free_array(data->envp);
	ft_print_error(MINI, command[0], msm);
	return (e);
}

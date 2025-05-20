/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_qd_killer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:58:12 by frivas            #+#    #+#             */
/*   Updated: 2025/05/20 15:58:50 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_qd_kill(char *str)
{
	char	*result;

	if (!str)
		return (NULL);
	result = ft_substr(str, 1, ft_strlen(str) - 2);
	if (!result)
		return (NULL);
	ft_free_ptr((void **)&str);
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:47:14 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/04/16 16:52:44 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_cmp(void *data, void *ref)
{
	char	*entry;
	char	*key;

	entry = (char *)data;
	key = (char *)ref;
	while (*key && *entry && *entry == *key)
	{
		key++;
		entry++;
	}
	if (*key == '\0' && *entry == '=')
		return (0);
	return (1);
}

int	ms_unset(t_mshell *data, char **data_ref)
{
	int	i;

	if (data_ref[1])
	{
		i = 1;
		while (data_ref[i])
		{
			if (data_ref[i][0] != '-')
				ft_list_remove_if(&data->env, data_ref[i], var_cmp);
			else
				return (ft_putendl_fd(SUBJECTOPTIONERROR, 2), 2);
			i++;
		}
	}
	return (0);
}

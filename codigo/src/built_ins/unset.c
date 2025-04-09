/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:47:14 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/04/09 15:54:47 by frivas           ###   ########.fr       */
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
				return (ft_putendl_fd("unset: subject doesn't allow opts.", 2), 2);
			i++;
		}
	}
	printf("unset\n"); // borrrar al terminar todas las pruebas!!!
	return (0);
}

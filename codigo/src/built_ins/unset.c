/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:47:14 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/04/25 16:40:42 by brivera@stu      ###   ########.fr       */
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
	if (*key == '\0' && (*entry == '=' || *entry == '\0'))
		return (0);
	return (1);
}

int	ms_unset(t_mshell *data, char **data_ref)
{
	int	i;
	int	exit;

	exit = 0;
	if (data_ref[1])
	{
		i = 1;
		if (data_ref[i][0] == '-')
			return (ft_putendl_fd(SUBJECTOPTIONERROR, 2), 2);
		while (data_ref[i])
		{
			if (ft_special_char(data_ref[i][0]))
			{
				ft_print_error("unset: ", data_ref[i], SPECIALCHAR);
				exit = 1;
				i++;
				continue ;
			}
			ft_list_remove_if(&data->env, data_ref[i], var_cmp);
			exit = 0;
			i++;
		}
	}
	ms_update_prompt(data);
	return (exit);
}

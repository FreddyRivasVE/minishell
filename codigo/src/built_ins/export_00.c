/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:41:48 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/04/25 17:25:07 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_args(char **command, t_mshell *data, int *exit_code, int *i)
{
	char	*arg;
	t_list	*new_node;

	while (command[*i])
	{
		if (ft_special_char(command[*i][0]))
		{
			ft_print_error("export: ", command[*i], SPECIALCHAR);
			*exit_code = 1;
			(*i)++;
			continue ;
		}
		arg = ft_strdup(command[*i]);
		if (!arg)
			return (perror("malloc"), ENOMEM);
		if ((ft_list_replace_cont(&data->env, arg, var_cmp)) == 0)
		{
			new_node = ft_lstnew(arg);
			if (!new_node)
				return (perror("malloc"), ft_free_ptr((void **)&arg), ENOMEM);
			ft_lstadd_back(&data->env, new_node);
		}
		(*i)++;
	}
	return (0);
}

int	ms_export(char **command, t_mshell *data)
{
	int	exit;
	int	result;
	int	i;

	exit = 0;
	i = 1;
	if (command[i])
	{
		if (command[i][0] == '-')
			return (ft_putendl_fd(SUBJECTEXPORTERROR, 2), 2);
		result = export_args(command, data, &exit, &i);
		if (result != 0)
			return (result);
	}
	else
		exit = ms_export_print_list(&data->env);
	return (exit);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:41:48 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/04/21 19:39:42 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_export_args(char **command, t_mshell *data, int *exit_code)
{
	char	*argt;
	t_list	*new_node;
	int		i;

	i = 1;
	while (command[i])
	{
		if (special_char(command[i][0]))
		{
			ft_print_error("export: ", command[i], SPECIALCHAR);
			*exit_code = 1;
		}
		argt = ft_strdup(command[i]);
		if (!argt)
			return (perror("malloc"), ENOMEM);
		if ((ft_list_replace_cont(&data->env, argt, var_cmp)) == 0)
		{
			new_node = ft_lstnew(argt);
			if (!new_node)
				return (perror("malloc"), ft_free_ptr(argt), ENOMEM);
			ft_lstadd_back(&data->env, new_node);
		}
		i++;
	}
	return (0);
}

int	ms_export(char **command, t_mshell *data)
{
	int	exit;
	int	result;

	exit = 0;
	if (command[1])
	{
		if (command[1][0] == '-')
			return (ft_putendl_fd(SUBJECTEXPORTERROR, 2), 2);
		result = handle_export_args(command, data, &exit);
		if (result != 0)
			return (result);
	}
	else
		exit = ms_export_print_list(&data->env);
	return (exit);
}

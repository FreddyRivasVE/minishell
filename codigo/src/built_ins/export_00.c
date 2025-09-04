/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:41:48 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/09/04 12:11:07 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ms_invalid_char(char c)
{
	return (ft_special_char(c) || ft_isredirection_char(c)
		|| c == '|' || c == '\'' || c == '\"' || c == '.');
}

static int	handle_export_assignment(char *command_arg, t_mshell *data)
{
	char	*arg;
	t_list	*new_node;

	arg = ms_add_dquotes(command_arg);
	if (!arg)
		return (perror("malloc"), ENOMEM);
	if ((ft_list_replace_cont(&data->env, arg, var_cmp)) == 0)
	{
		new_node = ft_lstnew(arg);
		if (!new_node)
			return (perror("malloc"), ft_free_ptr((void **)&arg), ENOMEM);
		ft_lstadd_back(&data->env, new_node);
	}
	return (0);
}

static int	handle_export_no_assignment(char *command_arg, t_mshell *data)
{
	char	*arg;
	char	*var_name;
	char	*existing_value;
	t_list	*new_node;

	var_name = ft_strjoin(command_arg, "=");
	if (!var_name)
		return (perror("malloc"), ENOMEM);
	existing_value = ft_list_extract_if(&data->env, var_name, var_cmp);
	if (!existing_value)
	{
		arg = ms_add_dquotes(command_arg);
		if (!arg)
			return (ft_free_ptr((void **)&var_name), perror("malloc"), ENOMEM);
		new_node = ft_lstnew(arg);
		if (!new_node)
			return (perror("malloc"), ft_free_ptr((void **)&arg),
				ft_free_ptr((void **)&var_name), ENOMEM);
		ft_lstadd_back(&data->env, new_node);
	}
	ft_free_ptr((void **)&var_name);
	return (0);
}

static int	export_args(char **command, t_mshell *data, int *exit_code, int *i)
{
	int	result;

	while (command[*i])
	{
		if (ms_invalid_char(command[*i][0]))
		{
			ft_print_error("export: ", command[*i], SPECIALCHAR);
			*exit_code = 1;
			(*i)++;
			continue ;
		}
		if (ft_strchr(command[*i], '='))
			result = handle_export_assignment(command[*i], data);
		else
			result = handle_export_no_assignment(command[*i], data);
		if (result != 0)
			return (result);
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

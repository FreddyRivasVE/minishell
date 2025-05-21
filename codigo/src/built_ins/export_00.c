/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:41:48 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/05/19 18:04:55 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_add_dquotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	int		flag;

	flag = 0;
	result = ft_calloc(ft_strlen(str) + 3, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != 0)
	{
		result[j] = str[i];
		if (str[i] == '=' && flag == 0)
		{
			result[++j] = '\"';
			flag = 1;
		}
		i++;
		j++;
	}
	if (flag == 1)
		result[j] = '\"';
	return (result);
}

static bool	ms_invalid_char(char c)
{
	return (ft_special_char(c) || ft_isredirection_char(c)
		|| c == '|' || c == '\'' || c == '\"');
}

static int	export_args(char **command, t_mshell *data, int *exit_code, int *i)
{
	char	*arg;
	t_list	*new_node;

	while (command[*i])
	{
		if (ms_invalid_char(command[*i][0]))
		{
			ft_print_error("export: ", command[*i], SPECIALCHAR);
			*exit_code = 1;
			(*i)++;
			continue ;
		}
		arg = ms_add_dquotes(command[*i]);
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

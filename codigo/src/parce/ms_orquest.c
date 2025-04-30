/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_orquest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:57:44 by frivas            #+#    #+#             */
/*   Updated: 2025/04/30 18:53:44 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_check_redir_access(char *tag, char *file_name)
{
	if (!file_name)
		return (-1);
	if (!ft_strcmp(tag, "INPUT") && access(file_name, R_OK) == -1)
		return (-1);
	if (!ft_strcmp(tag, "OUTPUT")
		&& access(file_name, F_OK | W_OK) == -1)
		return (-1);
	if (!ft_strcmp(tag, "OUTPUTAPPEND")
		&& access(file_name, F_OK | W_OK | R_OK) == -1)
		return (-1);
	return (0);
}

static int	ms_is_redirection(char *tag)
{
	return (!ft_strcmp(tag, "HEREDOC")
		|| !ft_strcmp(tag, "OUTPUTAPPEND")
		|| !ft_strcmp(tag, "INPUT")
		|| !ft_strcmp(tag, "OUTPUT" ));
}

static bool	ms_fill_commands(char *tag, char *split, t_mshell *data, int i)
{
	data->commands[i].type = ft_strdup(tag);
	data->commands[i].namefile = ft_strdup(split);
	if (!data->commands[i].type)
		return (ms_print_perror_malloc(data), false);
	return (true);
}

static bool	ms_orquest_redir(t_mshell *data, char ***split, char **tag)
{
	int		i;
	int		j;
	int		k;
	bool	flag;

	i = -1;
	k = 0;
	while (split[++i])
	{
		flag = false;
		j = 0;
		while (split[i][j])
		{
			if (ms_is_redirection(tag[k]) && !flag)
			{
				if (!ms_fill_commands(tag[k], split[i][j + 1], data, i))
					return (false);
				if (ms_check_redir_access(tag[k], split[i][j + 1]) == -1)
					flag = true;
			}
			j++;
			k++;
		}
	}
	return (true);
}

bool	ms_orquest(t_mshell *data, char ***split, char **tag)
{
	if (!ms_orquest_redir(data, split, tag))
		return (false);
	if (ms_orquest_command(data, split, tag) == -1)
		return (false);
	return (true);
}

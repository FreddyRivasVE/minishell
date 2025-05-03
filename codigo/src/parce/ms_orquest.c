/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_orquest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:57:44 by frivas            #+#    #+#             */
/*   Updated: 2025/05/03 13:29:38 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static int	ms_check_redir_access(char *tag, char *file_name)
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
}*/

static int	ms_is_redirection(char *tag)
{
	return (!ft_strcmp(tag, "HEREDOC")
		|| !ft_strcmp(tag, "OUTPUTAPPEND")
		|| !ft_strcmp(tag, "INPUT")
		|| !ft_strcmp(tag, "OUTPUT" ));
}

static bool	ms_fill_commands(char *tag, char *split, t_mshell *data, \
	int i, int l)
{
	data->redir[i][l].type = ft_strdup(tag);
	data->redir[i][l].namefile = ft_strdup(split);
	if (!data->redir[i][l].type)
		return (ms_print_perror_malloc(data), false);
	return (true);
}

static bool	ms_orquest_redir(t_mshell *data, char ***split, char **tag)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = -1;
	k = 0;
	while (split[++i])
	{
		j = 0;
		l = 0;
		while (split[i][j])
		{
			if (ms_is_redirection(tag[k]))
			{
				if (!ms_fill_commands(tag[k], split[i][j + 1], data, i, l))
					return (false);
				l++;
			}
			j++;
			k++;
		}
	}
	return (true);
}

bool	ms_orquest(t_mshell *data, char ***split, char **tag)
{
	if (!ms_reserve_memory_redir(data->input_row, data))
		return (false);
	if (!ms_orquest_redir(data, split, tag))
		return (false);
	if (ms_orquest_command(data, split, tag) == -1)
		return (false);
	ft_print_redir_array(data->redir); //borrar.
	ft_print_command_array(data->commands, data->pipesnum + 1); // borrar
	return (true);
}

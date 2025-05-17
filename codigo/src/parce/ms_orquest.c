/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_orquest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:57:44 by frivas            #+#    #+#             */
/*   Updated: 2025/05/16 15:05:54 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_is_redirection(char *tag)
{
	return (!ft_strcmp(tag, "HEREDOC")
		|| !ft_strcmp(tag, "OUTPUTAPPEND")
		|| !ft_strcmp(tag, "INPUT")
		|| !ft_strcmp(tag, "OUTPUT" ));
}

static bool	ms_fill_redir(char *tag, char *split, t_mshell *data, int *idx)
{
	if (!ft_strcmp(tag, "HEREDOC") && (split[0] == '\"' || split[0] == '\''))
		tag = "HEREDOCNE";
	data->redir[idx[0]][idx[1]].type = ft_strdup(tag);
	if (!ft_strcmp(tag, "HEREDOCNE"))
		data->redir[idx[0]][idx[1]].namefile = \
		ft_substr(split, 1, (ft_strlen(split) - 2));
	else
		data->redir[idx[0]][idx[1]].namefile = ft_strdup(split);
	if (!data->redir[idx[0]][idx[1]].type)
		return (ms_print_perror_malloc(data), false);
	return (true);
}

static bool	ms_handle_split(char **split, char **tag, t_mshell *data, int *ik)
{
	int	j;
	int	l;
	int	idx[2];

	j = 0;
	l = 0;
	while (split[j])
	{
		if (ms_is_redirection(tag[ik[1]]))
		{
			idx[0] = ik[0];
			idx[1] = l;
			if (!ms_fill_redir(tag[ik[1]], split[j + 1], data, idx))
				return (false);
			l++;
		}
		j++;
		ik[1]++;
	}
	return (true);
}

static bool	ms_orquest_redir(t_mshell *data, char ***split, char **tag)
{
	int	i;
	int	ik[2];

	i = 0;
	ik[1] = 0;
	while (split[i])
	{
		ik[0] = i;
		if (!ms_handle_split(split[i], tag, data, ik))
			return (false);
		i++;
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
	return (true);
}

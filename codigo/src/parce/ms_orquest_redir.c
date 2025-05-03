/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_orquest_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:47:55 by frivas            #+#    #+#             */
/*   Updated: 2025/05/03 13:32:22 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_redir_blocks(t_mshell *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(data->redir[i]);
		data->redir[i] = NULL;
		i++;
	}
}

static int	count_redirections(const char *str, int *index)
{
	int	count;

	count = 0;
	while (str[*index] != '\0' && str[*index] != '|')
	{
		if (ft_isredirection_char(str[*index]))
		{
			if (str[*index + 1] != '\0'
				&& ft_isredirection_char(str[*index + 1]))
				(*index)++;
			count++;
		}
		(*index)++;
	}
	return (count);
}

static bool	process_segment(const char *str, t_mshell *data, int *i, int *i_r)
{
	int	redir_count;

	redir_count = count_redirections(str, i);
	data->redir[*i_r] = ft_calloc(redir_count + 1, sizeof(t_redir));
	if (!data->redir[*i_r])
	{
		ms_print_perror_malloc(data);
		return (false);
	}
	(*i_r)++;
	if (str[*i] == '|')
		(*i)++;
	return (true);
}

bool	ms_reserve_memory_redir(char *str, t_mshell *data)
{
	int	i;
	int	i_r;

	i = 0;
	i_r = 0;
	while (str[i] != '\0')
	{
		if (!process_segment(str, data, &i, &i_r))
		{
			free_redir_blocks(data, i_r);
			return (false);
		}
	}
	return (true);
}

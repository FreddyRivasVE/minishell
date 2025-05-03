/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_orquest_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:47:55 by frivas            #+#    #+#             */
/*   Updated: 2025/05/03 18:47:00 by brivera@stu      ###   ########.fr       */
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

static int	count_redirections(char *str, int *index)
{
	int		count;
	bool	dqoute;
	bool	sqoute;

	sqoute = false;
	dqoute = false;
	count = 0;
	while (str[*index] != '\0')
	{
		sqoute = toggle_simples(str[*index], sqoute, dqoute);
		dqoute = toggle_doubles(str[*index], sqoute, dqoute);
		if (ft_isredirection_char(str[*index]) && !sqoute && !dqoute)
		{
			if (str[*index + 1] != '\0'
				&& ft_isredirection_char(str[*index + 1]))
				(*index)++;
			count++;
		}
		(*index)++;
		if (str[*index] == '|' && !sqoute && !dqoute)
			break ;
	}
	return (count);
}

static bool	process_segment(char *str, t_mshell *data, int *i, int *i_r)
{
	int		redir_count;

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
	int		i;
	int		i_r;

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

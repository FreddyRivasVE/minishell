/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input_row_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:55:27 by frivas            #+#    #+#             */
/*   Updated: 2025/04/30 16:34:05 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_heredoc_sequence(const char *str, int *i)
{
	if (str[*i] == '<' && str[*i + 1] == '<')
	{
		(*i) = (*i) + 2;
		while (str[*i] && ft_isspace(str[*i]))
			(*i)++;
		if (str[*i] == '\0')
			return (false);
		else
			return (true);
	}
	else
		(*i) = (*i) + 1;
	return (false);
}

static bool	ms_heredoc_live(char *str)
{
	int		i;
	bool	sq;
	bool	dq;

	if (ms_has_leading_pipe(str))
		return (false);
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (ft_isredirection_char(str[i]))
		return (false);
	sq = false;
	dq = false;
	while (str[i])
	{
		sq = toggle_simples(str[i], sq, dq);
		dq = toggle_doubles(str[i], sq, dq);
		if (ft_isredirection_char(str[i]) && !sq && !dq)
		{
			if (is_heredoc_sequence(str, &i))
				return (true);
		}
		else
			i++;
	}
	return (false);
}

static int	ms_execute_hd(t_mshell *data)
{
	if (!ms_redir_together(data))
		return (ENOMEM);
	if (!ms_split_input(data))
		return (ENOMEM);
	ms_heredoc_management(data);
	ft_close_heredoc_fds(data);
	ft_free_redir_array(data->redir);
	ft_free_command_array(data->commands, data->pipesnum + 1);
	return (2);
}

int	ms_input_row_validation(t_mshell *data)
{
	bool	heredoc;

	if (!data->input_row)
		return (ft_putendl_fd("malloc", 2), ENOMEM);
	if (!ms_check_quotation_marks(data->input_row))
		return (ft_putendl_fd(SYNTAX, 2), 2);
	heredoc = ms_heredoc_live(data->input_row);
	if (!ms_check_pipes(data->input_row))
	{
		if (heredoc)
			return (ft_putendl_fd(SYNTAXPIPE, 2), ms_execute_hd(data));
		else
			return (ft_putendl_fd(SYNTAXPIPE, 2), 2);
	}
	if (!ms_check_redir(data->input_row))
	{
		if (heredoc)
			return (ft_putendl_fd(SYNTAXREDIR, 2), ms_execute_hd(data));
		else
			return (ft_putendl_fd(SYNTAXREDIR, 2), 2);
	}
	return (0);
}

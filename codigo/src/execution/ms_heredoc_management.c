/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:55:42 by frivas            #+#    #+#             */
/*   Updated: 2025/06/04 11:05:21 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_heredoc_exit(t_redir *redir, t_mshell *data, char *line)
{
	redir->ok_tag = true;
	ft_free_ptr((void **)&line);
	close(redir->fd_pipe[1]);
	if (data->exits == ENOMEM)
		return (ENOMEM);
	if (g_signal == SIGINT)
		return (130);
	return (0);
}

static int	ms_heredoc(t_redir *redir, t_mshell *data, bool flag)
{
	char	*line;

	ms_set_signal_handler(MODE_HEREDOC);
	if (pipe(redir->fd_pipe) == -1)
		return (perror ("pipe"), 1);
	while (g_signal != SIGINT)
	{
		line = readline("> ");
		if (!line || (redir->namefile && !ft_strcmp(line, redir->namefile)))
		{
			if (!line)
				ft_putendl_fd(ERRORHEREDOC, 2);
			break ;
		}
		if (!flag)
			line = ms_expand_child(line, data);
		if (!line)
		{
			data->exits = ENOMEM;
			break ;
		}
		ft_putendl_fd(line, redir->fd_pipe[1]);
		ft_free_ptr((void **)&line);
	}
	return (ms_heredoc_exit(redir, data, line));
}

static bool	ms_handle_single_herdoc(t_redir *redir, t_mshell *data, bool *flag)
{
	if (!ft_strcmp(redir->type, "HEREDOC")
		|| !ft_strcmp(redir->type, "HEREDOCNE"))
	{
		if (!ft_strcmp(redir->type, "HEREDOCNE"))
			*flag = true;
		if (!redir->namefile || ft_strlen(redir->namefile) == 0)
			return (ft_close_heredoc_fds(data), false);
		data->hdflag = MODE_HEREDOC;
		data->exits = ms_heredoc(redir, data, *flag);
		if (data->exits == 130 || data->exits == ENOMEM)
		{
			g_signal = 0;
			ft_close_heredoc_fds(data);
			return (false);
		}
	}
	return (true);
}

bool	ms_heredoc_management(t_mshell *data)
{
	int		i;
	int		j;
	bool	flag;

	i = 0;
	while (data->redir[i])
	{
		j = 0;
		while (data->redir[i][j].type != NULL)
		{
			flag = false;
			if (!ms_handle_single_herdoc(&data->redir[i][j], data, &flag))
				return (false);
			j++;
		}
		i++;
	}
	data->hdflag = 0;
	return (true);
}

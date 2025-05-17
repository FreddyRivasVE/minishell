/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:55:42 by frivas            #+#    #+#             */
/*   Updated: 2025/05/09 12:57:29 by frivas           ###   ########.fr       */
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
		if (!line || !ft_strcmp(line, redir->namefile))
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

bool	ms_heredoc_management(t_mshell *data)
{
	int		i;
	int		j;
	bool	flag;

	i = 0;
	flag = false;
	while (data->redir[i])
	{
		j = 0;
		while (data->redir[i][j].type != NULL)
		{
			if (!ft_strcmp(data->redir[i][j].type, "HEREDOC")
				|| !ft_strcmp(data->redir[i][j].type, "HEREDOCNE"))
			{
				if (!ft_strcmp(data->redir[i][j].type, "HEREDOCNE"))
					flag = true;
				data->exits = ms_heredoc(&data->redir[i][j], data, flag);
				if (data->exits == 130 || data->exits == ENOMEM)
				{
					g_signal = 0;
					return (ft_close_heredoc_fds(data), false);
				}
			}
			flag = false;
			j++;
		}
		i++;
	}
	return (true);
}

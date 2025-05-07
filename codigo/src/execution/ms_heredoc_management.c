/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:55:42 by frivas            #+#    #+#             */
/*   Updated: 2025/05/07 17:00:16 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_heredoc(t_redir *redir)
{
	char	*line;

	ms_set_signal_handler(MODE_HEREDOC);
	if (pipe(redir->fd_pipe) == -1)
		return (perror ("pipe"), 1);
	while (g_signal != SIGINT)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putendl_fd(ERRORHEREDOC, 2);
			break ;
		}
		if (!ft_strcmp(line, redir->namefile))
			break ;
		ft_putendl_fd(line, redir->fd_pipe[1]);
		ft_free_ptr((void **)&line);
	}
	redir->ok_tag = true;
	ft_free_ptr((void **)&line);
	close(redir->fd_pipe[1]);
	if (g_signal == SIGINT)
		return (130);
	return (0);
}

bool	ms_heredoc_management(t_mshell *data)
{
	int		i;
	int		j;

	i = 0;
	while (data->redir[i])
	{
		j = 0;
		while (data->redir[i][j].type != NULL)
		{
			if (!ft_strcmp(data->redir[i][j].type, "HEREDOC"))
			{
				data->exits = ms_heredoc(&data->redir[i][j]);
				if (data->exits == 130)
				{
					g_signal = 0;
					ft_close_heredoc_fds(data);
					return (true);
				}
			}
			j++;
		}
		i++;
	}
	return (false);
}

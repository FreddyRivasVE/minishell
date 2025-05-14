/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_heredoc_fds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:35:54 by frivas            #+#    #+#             */
/*   Updated: 2025/05/14 19:52:43 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_heredoc_fds(t_mshell *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->redir[i])
	{
		j = 0;
		while (data->redir[i][j].type != NULL)
		{
			if (!ft_strcmp(data->redir[i][j].type, "HEREDOC")
			&& data->redir[i][j].ok_tag == true)
			{
				close(data->redir[i][j].fd_pipe[0]);
				data->redir[i][j].ok_tag = false;
			}
			j++;
		}
		i++;
	}
}

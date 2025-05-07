/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:14:29 by frivas            #+#    #+#             */
/*   Updated: 2025/05/05 18:32:37 by frivas           ###   ########.fr       */
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

int	ms_heredoc(t_redir *redir)
{
	char	*line;
	char	*temp ;

	ms_set_signal_handler(MODE_HEREDOC);
	temp = ft_calloc(1024 + 1, sizeof(char)); //borrar 
	if (pipe(redir->fd_pipe) == -1)
		return (perror ("pipe"), 1);
	//close (redir->fd_pipe[0]);
	while (g_signal != SIGINT)
	{
		line = readline("> ");
		if (!line)
		{
				ft_putendl_fd(ERRORHEREDOC, 2);
				close(redir->fd_pipe[1]);
				return (0);
			}
			if (!ft_strcmp(line, redir->namefile))
				break ;
			ft_putendl_fd(line, redir->fd_pipe[1]);
			ft_free_ptr((void **)&line);
	}
	ft_free_ptr((void **)&line);
	read (redir->fd_pipe[0], temp,1024); //borrar
	printf ("lo que hay en pipe de %s %s\n", redir->namefile, temp); //borrar
	free(temp); //borrar
	close (redir->fd_pipe[0]);
	close(redir->fd_pipe[1]);
	if (g_signal == SIGINT)
		return (130);
	return (0);
}


void	ms_redir_management(t_mshell *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->redir[i])
	{
		j = 0;
		while (data->redir[i][j].type != NULL)
		{
			printf("valor de i: %d y j: %d y redir %s\n", i, j, data->redir[i][j].type);
			if (!ft_strcmp(data->redir[i][0].type, "HEREDOC"))
				data->exits = ms_heredoc(&data->redir[i][j]);
			// if (data->exits == 130)
			// {
			// 	g_signal = 0;
			// 	return ;
			// }
			j++;
		}
		i++;
	}
}

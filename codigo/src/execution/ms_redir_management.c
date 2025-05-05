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
	pid_t	pid;
	int		status;
	char	*line;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	redir->fd = 0;
	if (pid == 0)
	{
		ms_set_signal_handler(MODE_HEREDOC);
		redir->fd = open(redir->namefile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (redir->fd == -1)
		{
			perror("here_doc");
			exit(1);
		}
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				ft_putendl_fd(ERRORHEREDOC, 2);
				close(redir->fd);
				exit(0);
			}
			if (!ft_strcmp(line, redir->namefile))
			{
				free(line);
				break ;
			}
			ft_putendl_fd(line, redir->fd);
			free(line);
		}
		free(line);
		close(redir->fd);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			return (130);
		else if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
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
			if (!ft_strcmp(data->redir[i][j].type, "HEREDOC"))
				data->exits = ms_heredoc(&data->redir[i][j]);
			if (data->exits == 130)
				return ;
			j++;
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:14:29 by frivas            #+#    #+#             */
/*   Updated: 2025/05/07 17:38:13 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_check_redir_access(char *tag, char *file_name)
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
}

void	ms_redir_access(t_mshell *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->redir[i])
	{
		j = 0;
		while (data->redir[i][j].type != NULL)
		{
			if (ms_check_redir_access(data->redir[i][j].type, \
				data->redir[i][j].namefile) == -1)
				data->redir[i][j].ok_tag = false;
			else
				data->redir[i][j].ok_tag = true;
			printf("OK_TAG: %d\n", data->redir[i][j].ok_tag); //borrar
			j++;
		}
		i++;
	}
}

/* void	ms_redir_fill(t_mshell *data)
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
				data->commands[i].fd_input = data->redir[i][j].fd_pipe[0];
			if (!ft_strcmp(data->redir[i][j].type, "INPUT"))
				data->commands[i].input_name = ft_strdup(data->redir[i][j].namefile);
			if (!ft_strcmp(data->redir[i][j].type, "OUTPUT"))
			{
				data->commands[i].output_name = ft_strdup(data->redir[i][j].namefile);
				data->commands[i].type_output = ft_strdup(data->redir[i][j].type);
				data->commands[i].fd_output = open(data->redir[i][j].namefile , O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (data->commands[i].fd_output != -1)
					close (data->commands[i].fd_output);
			}
			if (!ft_strcmp(data->redir[i][j].type, "OUTPUTAPPEND"))
			{
				data->commands[i].output_name = ft_strdup(data->redir[i][j].namefile);
				data->commands[i].type_output = ft_strdup(data->redir[i][j].type);
				data->commands[i].fd_output = open(data->redir[i][j].namefile , O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (data->commands[i].fd_output != -1)
					close (data->commands[i].fd_output);
			}
			if (!data->redir[i][j].ok_tag)
				break ;
			j++;
		}
		i++;
	}
	
} */

void	ms_redir_management(t_mshell *data)
{
	if (ms_heredoc_management(data))
		return ;
	ms_redir_access(data);
	//ms_redir_fill(data);
}

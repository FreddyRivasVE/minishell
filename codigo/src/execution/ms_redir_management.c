/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:14:29 by frivas            #+#    #+#             */
/*   Updated: 2025/05/18 18:44:12 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_check_redir_access(char *tag, char *file_name)
{
	if (!file_name)
		return (-1);
	if (!ft_strcmp(tag, "INPUT") && access(file_name, F_OK) == -1)
		return (-1);
	if (!ft_strcmp(tag, "OUTPUT"))
	{
		if (access(file_name, F_OK) != -1)
		{
			if (access(file_name, W_OK) == -1)
				return (-1);
		}
		return (0);
	}
	if (!ft_strcmp(tag, "OUTPUTAPPEND"))
	{
		if (access(file_name, F_OK) != -1)
		{
			if (access(file_name, W_OK | R_OK) == -1)
				return (-1);
		}
		return (0);
	}
	return (0);
}

static void	ms_redir_access(t_mshell *data)
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
			j++;
		}
		i++;
	}
}

static bool	ms_redir_fill_output(t_mshell *data, int i, int j)
{
	if (!ft_strcmp(data->redir[i][j].type, "OUTPUT")
		|| !ft_strcmp(data->redir[i][j].type, "OUTPUTAPPEND"))
	{
		ft_free_ptr((void **)&data->commands[i].output_name);
		data->commands[i].output_name = ft_strdup(data->redir[i][j].namefile);
		if (!data->commands[i].output_name)
			return (ms_print_perror_malloc(data), false);
		ft_free_ptr((void **)&data->commands[i].type_output);
		data->commands[i].type_output = ft_strdup(data->redir[i][j].type);
		if (!data->commands[i].output_name)
			return (ms_print_perror_malloc(data), false);
		if (!ft_strcmp(data->redir[i][j].type, "OUTPUT"))
			data->commands[i].fd_output = open(data->redir[i][j].namefile, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (!ft_strcmp(data->redir[i][j].type, "OUTPUTAPPEND"))
			data->commands[i].fd_output = open(data->redir[i][j].namefile, \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (data->commands[i].fd_output != -1)
			close (data->commands[i].fd_output);
		data->commands[i].fd_output = 0;
	}
	return (true);
}

static bool	ms_redir_fill_input(t_mshell *data, int i, int j, char *dredir)
{
	if (!ft_strcmp(dredir, "HEREDOC") || !ft_strcmp(dredir, "HEREDOCNE"))
	{
		if (data->commands[i].input_name != NULL
			&& (!ft_strcmp(data->commands[i].input_name, "HEREDOC")
				|| !ft_strcmp(data->commands[i].input_name, "HEREDOCNE")))
			close(data->commands[i].fd_input);
		ft_free_ptr((void **)&data->commands[i].input_name);
		data->commands[i].input_name = ft_strdup(data->redir[i][j].type);
		if (!data->commands[i].input_name)
			return (ms_print_perror_malloc(data), false);
		data->commands[i].fd_input = data->redir[i][j].fd_pipe[0];
	}
	if (!ft_strcmp(data->redir[i][j].type, "INPUT"))
	{
		if (data->commands[i].input_name != NULL
			&& (!ft_strcmp(data->commands[i].input_name, "HEREDOC")
				|| !ft_strcmp(data->commands[i].input_name, "HEREDOCNE")))
			close(data->commands[i].fd_input);
		ft_free_ptr((void **)&data->commands[i].input_name);
		data->commands[i].input_name = ft_strdup(data->redir[i][j].namefile);
		if (!data->commands[i].input_name)
			return (ms_print_perror_malloc(data), false);
		data->commands[i].fd_input = 0;
	}
	return (true);
}

bool	ms_redir_management(t_mshell *data)
{
	int		i;
	int		j;
	char	*dredir;

	if (!ms_heredoc_management(data))
		return (false);
	ms_redir_access(data);
	i = 0;
	while (data->redir[i])
	{
		j = 0;
		while (data->redir[i][j].type != NULL)
		{
			dredir = data->redir[i][j].type;
			if (!ms_redir_fill_input(data, i, j, dredir))
				return (false);
			if (!ms_redir_fill_output(data, i, j))
				return (false);
			if (!data->redir[i][j].ok_tag)
				break ;
			j++;
		}
		i++;
	}
	return (true);
}

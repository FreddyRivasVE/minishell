/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_orquest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:57:44 by frivas            #+#    #+#             */
/*   Updated: 2025/04/29 19:21:03 by frivas           ###   ########.fr       */
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

static int	ms_is_redirection(char *tag)
{
	return (!ft_strcmp(tag, "HEREDOC")
		|| !ft_strcmp(tag, "OUTPUTAPPEND")
		|| !ft_strcmp(tag, "INPUT")
		|| !ft_strcmp(tag, "OUTPUT" ));
}

static void	ms_orquest_redir(t_mshell *data, char ***split, char **tag)
{
	int		i;
	int		j;
	int		k;
	bool	flag;

	i = 0;
	k = 0;
	while (split[i])
	{
		flag = false;
		j = 0;
		while (split[i][j])
		{
			if (ms_is_redirection(tag[k]) && !flag)
			{
				data->commands[i].type = ft_strdup(tag[k]);
				data->commands[i].namefile = ft_strdup(split[i][j + 1]);
				printf("estructura: %d type: %s namefile: %s\n", i, data->commands[i].type, data->commands[i].namefile); //Borrar.
				if (ms_check_redir_access(tag[k], split[i][j + 1]) == -1)
					flag = true;
			}
			j++;
			k++;
		}
		i++;
	}
}

void	ms_orquest(t_mshell *data, char ***split, char **tag)
{
	ms_orquest_redir(data, split, tag);
	if (ms_orquest_command(data, split, tag) == -1)
		printf("recordemos blindar si falla la asignacion de memoria en la struct comandos");
}

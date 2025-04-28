/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pre_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:45:33 by frivas            #+#    #+#             */
/*   Updated: 2025/04/28 17:32:53 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_set_redir_type(char *inputs, char **tag)
{
	if (inputs[0] == '<' && inputs[1] == '<')
		*tag = "HEREDOC";
	else if (inputs[0] == '>' && inputs[1] == '>')
		*tag = "OUTPUTAPPEND";
	else if (inputs[0] == '<')
		*tag = "INPUT";
	else if (inputs[0] == '>')
		*tag = "OUTPUT";
}

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

static int	ms_process_redir_token(char *inputype, char **tag, char *file_name)
{
	(void) file_name;
	ms_set_redir_type(inputype, tag);
	//if (ms_check_redir_access(*tag, file_name) == -1)
	//	return (-1);
	return (0);
}

void	ms_pre_redir(t_mshell *data)
{
	int		i;
	int		j;
	int		k;
	char	***inputs;

	inputs = data->inputs->splitaftpipes;
	i = 0;
	k = 0;
	while (inputs[i])
	{
		j = 0;
		while (inputs[i][j])
		{
			if (!ft_strcmp(data->inputs->tag[k], "REDIR"))
			{
				if (ms_process_redir_token(inputs[i][j], \
					&data->inputs->tag[k], inputs[i][j + 1]) == -1)
					break ;
			}
			printf("RONDA: %d vuelta j:%d str:%s tag: %s\n", i, j, inputs[i][j], data->inputs->tag[k]);
			printf("vuelta k: %d\n", k);
			j++;
			k++;
		}
		i++;
		printf("vuelta: %d\n", i);
	}
}

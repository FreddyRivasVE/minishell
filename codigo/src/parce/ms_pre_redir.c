/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pre_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:45:33 by frivas            #+#    #+#             */
/*   Updated: 2025/04/25 17:29:27 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_set_redir_type(t_redir *redir, char *inputs)
{
	if (inputs[0] == '<' && inputs[1] == '<')
		redir->type = "HEREDOC";
	else if (inputs[0] == '>' && inputs[1] == '>')
		redir->type = "OUTPUTAPPEND";
	else if (inputs[0] == '<')
		redir->type = "INPUT";
	else if (inputs[0] == '>')
		redir->type = "OUTPUT";
}

static int	ms_check_redir_access(t_redir *redir)
{
	if (!redir->namefile)
		return (-1);
	if (!ft_strcmp(redir->type, "INPUT") && access(redir->namefile, R_OK) == -1)
		return (-1);
	if (!ft_strcmp(redir->type, "OUTPUT")
		&& access(redir->namefile, F_OK | W_OK) == -1)
		return (-1);
	if (!ft_strcmp(redir->type, "OUTPUTAPPEND")
		&& access(redir->namefile, F_OK | W_OK | R_OK) == -1)
		return (-1);
	return (0);
}

static int	ms_process_redir_token(t_redir *redir, char **inputs, int j)
{
	if (!inputs[j + 1])
		return (-1);
	ft_free_ptr((void **)&redir->namefile);
	redir->namefile = ft_strdup(inputs[j + 1]);
	ms_set_redir_type(redir, inputs[j]);
	if (ms_check_redir_access(redir) == -1)
		return (-1);
	return (0);
}

void	ms_pre_redir(t_mshell *data)
{
	int		i;
	int		j;
	t_redir	*redir;
	char	***inputs;

	inputs = data->inputs->splitaftpipes;
	redir = &data->commands->redir;
	i = 0;
	while (inputs[i])
	{
		j = 0;
		redir->namefile = NULL;
		while (inputs[i][j])
		{
			if (inputs[i][j][0] == '<' || inputs[i][j][0] == '>')
			{
				if (ms_process_redir_token(redir, inputs[i], j) == -1)
					return ;
			}
			j++;
		}
		i++;
	}
}

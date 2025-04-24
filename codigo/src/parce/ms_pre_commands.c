/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pre_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:45:33 by frivas            #+#    #+#             */
/*   Updated: 2025/04/24 19:22:08 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pre_commands(t_mshell *data)
{
	int			i;
	int			j;
	t_redir		*redir;
	char		***inputs;

	inputs = data->inputs->splitaftpipes;
	redir = &data->commands->redir;
	i = 0;
	while (inputs[i])
	{
		j = 0;
		redir->namefile = NULL;
		while (inputs[i][j])
		{
			if (inputs[i][j][0] == '<' || inputs[i][j][0] == '>'
				|| (inputs[i][j][0] == '<' && inputs[i][j][1] == '<')
					|| (inputs[i][j][0] == '>' && inputs[i][j][1] == '>'))
			{
				ft_free_ptr(redir->namefile);
				redir->namefile = ft_strdup(inputs[i][j + 1]);
				if (inputs[i][j][0] == '<')
				{
					redir->type = "INPUT";
					if (access(redir->namefile, R_OK) == -1)
						break ;
				}
				else if (inputs[i][j][0] == '>')
				{
					redir->type = "OUTPUT";
					if (access(redir->namefile, F_OK | W_OK) == -1)
						return ;
				}
				else if (inputs[i][j][0] == '<' && inputs[i][j][1] == '<')
					redir->type = "HEREDOC";
				else if (inputs[i][j][0] == '>' && inputs[i][j][1] == '>')
				{
					redir->type = "OUTPUTAPPEND";
					if (access(redir->namefile, F_OK | W_OK | R_OK) == -1)
						return ;
				}
			}
			j++;
		}
		i ++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pre_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:45:33 by frivas            #+#    #+#             */
/*   Updated: 2025/04/24 17:11:58 by frivas           ###   ########.fr       */
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
	redir = malloc(sizeof(t_redir));
	i = 0;
	while (inputs[i])
	{
		j = 0;
		redir->namefile = NULL;
		while (inputs[i][j])
		{
			if (!ft_strcmp(inputs[i][j], "<") || !ft_strcmp(inputs[i][j], ">")
				|| !ft_strcmp(inputs[i][j], "<<")
					|| !ft_strcmp(inputs[i][j], ">>"))
			{
				ft_free_ptr(redir->namefile);
				redir->namefile = ft_strdup(inputs[i][j + 1]);
				if (!ft_strcmp(inputs[i][j], "<"))
					redir->type = "INPUT";
				else if (!ft_strcmp(inputs[i][j], ">"))
					redir->type = "OUTPUT";
				else if (!ft_strcmp(inputs[i][j], "<<"))
					redir->type = "HEREDOC";
				else if (!ft_strcmp(inputs[i][j], ">>"))
					redir->type = "OUTPUTAPPEND";
				printf("type: %s name: %s\n", redir->type, redir->namefile);
				if (access(redir->namefile, F_OK | R_OK | W_OK | X_OK) == -1)
					return ;	
			}
			j++;
		}
		i ++;
	}
}

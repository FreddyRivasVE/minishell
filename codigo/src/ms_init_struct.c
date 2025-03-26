/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:16:48 by frivas            #+#    #+#             */
/*   Updated: 2025/03/26 15:25:28 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_get_env_line(char	*env)
{
	char	*env_line;

	env_line = ft_strdup(env);
	//hay que sumar + 1 al SHLVL;
	return (env_line);
}

t_list	*ms_get_env(char **env)
{
	int		i;
	char	*envread;
	t_list	*new_node;
	t_list	*env_list;

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		envread = ms_get_env_line(env[i]);
		new_node = ft_lstnew(envread);
		if (!new_node)
		{
			perror("Error al crear nodo\n");
			free(envread);
			ft_lstclear(&env_list, free);
		}
		ft_lstadd_back(&env_list, new_node);
		i++;
	}
	return (env_list);
}

void	ms_init_struct(t_mshell *data, char **env)
{
	rl_catch_signals = 0;
	data->pipes = 0;
	data->redirs = 0;
	data->commands = 0;
	data->exits = 0;
	data->inputs = 0;
	data->env = 0;
	data->env = ms_get_env(env);
	ms_get_pront(data);
	ft_lstclear(&data->env, free);
}

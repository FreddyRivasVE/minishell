/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:16:48 by frivas            #+#    #+#             */
/*   Updated: 2025/03/24 16:16:39 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_list **lst)
{
	t_list *current = *lst;
	
	while (current != NULL)
	{  
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
}

char *get_env_line(char	*env)
{
	char	*env_line;
	
	env_line = ft_strdup(env);
	return (env_line);
}

t_list	*ms_get_env(char **env)
{
	int		i;
	char	*content;
	t_list	*new_node;
	t_list	*env_list;

	i = 0;
	while (env[i])
	{
		content = get_env_line(env[i]);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			printf("Error al crear nodo\n");
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
	data->env = ms_get_env(env);
	print_list(&data->env);  // Para probar si copia correctamente
}

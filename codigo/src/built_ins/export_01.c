/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:36:51 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/04/05 19:51:48 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list_sorted(t_list **lst)
{
	t_list	*current;

	current = *lst;
	while (current != NULL)
	{
		if (current->content != NULL)
			printf("declare -x %s\n", (char *)current->content);
		current = current->next;
	}
}

t_list	*ms_copy_export_env(t_list **env)
{
	char	*envread;
	t_list	*new_node;
	t_list	*env_list;
	t_list	*current;

	env_list = NULL;
	current = *env;
	while (current != NULL)
	{
		envread = ft_strdup(current->content);
		if (!envread)
			return (perror("malloc"), ft_lstclear(&env_list, free), env_list);
		new_node = ft_lstnew(envread);
		if (!new_node)
			return (perror("molloc nodo"), ms_free_ptr((void *)envread),
				ft_lstclear(&env_list, free), env_list);
		ft_lstadd_back(&env_list, new_node);
		current = current->next;
	}
	return (env_list);
}

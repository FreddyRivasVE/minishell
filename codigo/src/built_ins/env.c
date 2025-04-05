/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:52:54 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/04/05 18:14:43 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list_content_char(t_list **lst)
{
	t_list	*current;

	current = *lst;
	while (current != NULL)
	{
		if (current->content != NULL
			&& ft_strchr((char *)current->content, '='))
			printf("%s\n", (char *)current->content);
		current = current->next;
	}
}

//env sin opciones o argumentos
int	ms_env(char **command, t_list **env)
{
	if (command[1])
	{
		ft_putendl_fd("env: subject doesn't allow arguments or options", 2);
		return (2);
	}
	print_list_content_char(env);
	return (0);
}

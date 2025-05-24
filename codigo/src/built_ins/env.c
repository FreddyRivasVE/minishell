/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:52:54 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/05/11 12:34:23 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_list_content_char(t_list **lst)
{
	t_list	*current;
	char	*content;
	int		i;

	current = *lst;
	while (current != NULL)
	{
		if (current->content != NULL
			&& ft_strchr((char *)current->content, '='))
		{
			i = 0;
			 content = (char *)current->content;
			while (content[i])
			{
				if (content[i] == '\"')
					i++;
				write(1, &content[i], 1);
				if (content[i] != '\0')
					i++;
			}
			write(1, "\n", 1);
		}
		current = current->next;
	}
}

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

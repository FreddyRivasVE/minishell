/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:52:54 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/05/27 11:41:34 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_list_content_char(t_list **lst)
{
	t_list	*actual;
	char	*content;
	int		i;

	actual = *lst;
	while (actual != NULL)
	{
		if (actual->content != NULL && ft_strchr((char *)actual->content, '='))
		{
			content = (char *)actual->content;
			i = 0;
			while (content[i] != '\0')
			{
				if (content[i] == '\"')
				{
					i++;
					continue ;
				}
				write(1, &content[i], 1);
				i++;
			}
			write(1, "\n", 1);
		}
		actual = actual->next;
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
